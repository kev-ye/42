import {
  Controller,
  Get,
  Post,
  Put,
  Delete,
  Req,
  Res,
  Body,
  UseGuards,
  Redirect,
  Inject,
  Param,
} from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';

import * as twoFa from 'node-2fa';

import { UserDto, LimitedUserDto } from './dto/user.dto';
import { UserService } from './user.service';
import { UserGuard } from '../auth/user.guard';
import { RefererGuard } from '../auth/referer.guard';
import { Response } from 'express';

@Controller('user')
export class UserController {
  constructor(
    @Inject('USER_SERVICE') private readonly userService: UserService,
  ) {}

  @Get('/')
  @UseGuards(RefererGuard)
  async getUsers(): Promise<UserDto[]> {
    return await this.userService.getUsers();
  }

  @Get('id')
  @UseGuards(UserGuard)
  async getUserByCredentials(@Req() req: any, @Res() res: any): Promise<void> {
    const id = req.session.userId;
    const user: UserDto = await this.userService.getUserById(id);

    if (user) res.status(200).json(user);
    else
      res.status(403).json({
        Forbidden: `Can't found user by id: ${id}`,
      });
  }

  @Get('id/:id')
  @UseGuards(UserGuard)
  async getUserById(@Param('id') id: string) {
    return await this.userService.getUserById(id);
  }

  @Get('name/:name')
  @UseGuards(UserGuard)
  async getUserByName(
    @Req() req: any,
    @Res() res: any,
    @Param('name') name: string,
  ): Promise<void> {
    const id = req.session.userId;
    const user: UserDto = await this.userService.getUserById(id);

    if (user) {
      const getUserByName: UserDto = await this.userService.getUserByName(name);
      if (getUserByName) res.status(200).json(getUserByName);
      else res.status(200).json(null);
    } else
      res.status(403).json({
        Forbidden: `Can't found user by name: ${name}`,
      });
  }

  @Put('create')
  @UseGuards(UserGuard)
  async createUser(
    @Req() req: any,
    @Res() res: any,
    @Body() name: any,
  ): Promise<void> {
    const id: string = req.session.userId;
    const user: UserDto = await this.userService.getUserById(id);

    if (user) {
      const newUser: UserDto | null = await this.userService.createUser(
        user,
        name.name,
      );
      if (!newUser) res.status(201).json({});
      else res.status(201).json(newUser);
    } else
      res.status(403).json({
        Forbidden: `Can't find user by id: ${id}`,
      });
  }

  @Post('create/verify')
  @UseGuards(UserGuard)
  async nameVerify(@Body() name: any): Promise<boolean> {
    return await this.userService.nameFormatVerify(name.name);
  }

  @Put('update')
  @UseGuards(UserGuard)
  async updateUserById(
    @Body() user: UserDto,
    @Res() res: Response,
  ): Promise<UserDto> {
    if (user.name && !(await this.userService.nameFormatVerify(user.name))) {
      res.status(403).send('Username formatting is incorrect');
      return;
    }
    if (user.name) {
      const tmp = await this.userService.getUserByName(user.name);
      if (tmp) {
        if (user.id != tmp.id) {
          res.status(403).send('Username is already being used\n');
          return;
        }
      }
    }
    res.status(200).send();
    return this.userService.updateUser(user);
  }

  /*
   * Auth
   */

  /*  login/logout */

  @Get('auth/42/login')
  @UseGuards(AuthGuard('42'))
  // eslint-disable-next-line @typescript-eslint/no-empty-function
  async ftLogIn(): Promise<void> {}

  @Get('auth/42/callback')
  @UseGuards(AuthGuard('42'))
  ftAuthCallback(@Req() req: any, @Res() res: any): void {
    const user: LimitedUserDto = req.user;

    // set session when user exist
    if (user) req.session.userId = user.id;
    res.redirect('http://localhost:80/main');
  }

  @Get('isLogin')
  @UseGuards(RefererGuard)
  async isLogin(@Req() req: any): Promise<boolean> {
    const id = req.session.userId;
    const user = await this.userService.getUserById(id);

    return !!user;
  }

  @Get('isLogin/refresh')
  @UseGuards(UserGuard)
  isLoginRefresh(@Res() res: any) {
    // refresh session expire time
    res.status(200).json({
      ok: 'Refresh',
    });
  }

  @Post('auth/logout')
  @UseGuards(UserGuard)
  async logOut(@Req() req: any, @Res() res: any) {
    const user: UserDto = await this.userService.getUserById(
      req.session.userId,
    );
    if (user) {
      user.online = 0;
      await this.userService.updateUser(user);
    }
    // eslint-disable-next-line @typescript-eslint/no-empty-function
    req.session.destroy(() => {});
    res.status(200).json({
      ok: 'ok',
    });
  }

  /* Two-factor authentication */

  @Post('auth/2fa/generate')
  @UseGuards(UserGuard)
  async twoFaGenerate(@Req() req: any, @Res() res: any): Promise<void> {
    const user: UserDto = await this.userService.getUserById(
      req.session.userId,
    );

    if (user) {
      const newSecret = twoFa.generateSecret({
        name: 'TwoFactorAuthentication',
        account: user.login,
      });
      user.twoFactorSecret = newSecret.secret;
      user.twoFactorQR = newSecret.qr;
      await this.userService.updateUser(user);

      res.status(200).json(newSecret);
    } else
      res.status(401).json({
        'Error message': 'Unauthorized Access',
      });
  }

  @Delete('auth/2fa/turnoff')
  @UseGuards(UserGuard)
  async twoFaTurnOff(@Req() req: any, @Res() res: any): Promise<void> {
    const user: UserDto = await this.userService.getUserById(
      req.session.userId,
    );

    if (user) {
      user.twoFactorSecret = '';
      user.twoFactorQR = '';
      await this.userService.updateUser(user);

      res.status(200).json({
        ok: 'ok',
      });
    } else
      res.status(401).json({
        'Error message': 'Unauthorized Access',
      });
  }

  @Post('auth/2fa/verify')
  @UseGuards(UserGuard)
  async twoFaVerify(
    @Req() req: any,
    @Res() res: any,
    @Body() body: any,
  ): Promise<void> {
    const user: UserDto = await this.userService.getUserById(
      req.session.userId,
    );

    if (user) {
      const result = twoFa.verifyToken(user.twoFactorSecret, body.token);
      if (result && result.delta === 0) {
        user.online = 1;
        await this.userService.updateUser(user);
      }
      res.status(200).json(result ? result : { delta: -2 });
    } else
      res.status(401).json({
        'Error message': 'Unauthorized Access',
      });
  }
}
