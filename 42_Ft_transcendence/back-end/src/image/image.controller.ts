import {
  Controller,
  Delete,
  Get,
  Inject,
  Logger,
  Param,
  Post,
  Req,
  Res,
  Response,
  StreamableFile,
  UploadedFile,
  UseGuards,
  UseInterceptors,
} from '@nestjs/common';
import { FileInterceptor } from '@nestjs/platform-express';
import * as fs from 'fs';
import { diskStorage } from 'multer';
import { join } from 'path';
import { UserGuard } from 'src/auth/user.guard';
import { UserService } from 'src/user/user.service';

@Controller('image')
export class ImageController {
  constructor(@Inject('USER_SERVICE') private userService: UserService) {}

  @Post('upload/:id')
  @UseGuards(UserGuard)
  @UseInterceptors(
    FileInterceptor('image', {
      storage: diskStorage({
        destination: '../uploads',
        filename: (req, file, cb) => {
          cb(
            null,
            (Math.random() + 1).toString(36).substring(7) +
              req.headers.extension,
          );
        },
      }),
    }),
  )
  async uploadFile(
    @UploadedFile() file: Express.Multer.File,
    @Param('id') id: string,
    @Req() req: any
  ) {
    //check cookie if authenticated
    if (req.session.userId != id)
      return;

    const user = await this.userService.getUserById(id);
    try {
      if (user && user.avatar.length > 0)
        fs.unlinkSync('../uploads/' + user.avatar);
    } catch {
    }

    // modify by kaye bcs use updateUserById not run
    if (user) {
      user.avatar = file.filename;
      await this.userService.updateUser(user);
    }
  }

  @Get()
  @UseGuards(UserGuard)
  async getDefaultAvatar(@Res() res: any) {
    let file;
    try {
      file = fs.createReadStream('./static/default_avatar.png');
    } catch {
      return; 
    }
    res.set('Content-Disposition', 'inline');
    return new StreamableFile(file);
  }

  @Get('user/:id')
  @UseGuards(UserGuard)
  async getImageFromUser(
    @Param('id') id: string,
    @Response({ passthrough: true }) res: any,
  ) {
    const user = await this.userService.getUserById(id);

    let file;
    if (user && user.avatar && user.avatar.length > 0) {
      try {
        file = fs.createReadStream(join('../uploads/', user.avatar));
      } catch {
        Logger.error('Could not load picture');
        file = fs.createReadStream('./static/default_avatar.png');
      }
    } else file = fs.createReadStream('./static/default_avatar.png');

    res.set('Content-Disposition', 'inline'); //'attachment; filename=' + user.picture)
    res.set('Pragma-directive', 'no-cache');
    res.set('Cache-control', 'no-cache');
    res.set('Pragma', 'no-cache');
    res.set('Expires', '0');
    return new StreamableFile(file);
  }

  @Get(':id')
  @UseGuards(UserGuard)
  async getImage(
    @Param('id') id: string,
    @Response({ passthrough: true }) res: any,
  ) {
    // const user = await this.userService.getUserById(id);

    let file;

    try {
      file = fs.createReadStream(join('../uploads/', id));
    } catch {
      file = fs.createReadStream('./static/default_avatar.png');
    }

    res.set('Content-Disposition', 'inline'); //'attachment; filename=' + user.picture)
    return new StreamableFile(file);
  }

  @Delete(':id')
  @UseGuards(UserGuard)
  async deleteImage(@Param('id') id: string, @Req() req: any) {
    if (req.session.userId != id)
      return ;
    const user = await this.userService.getUserById(id);

    if (user && user.avatar && user.avatar.length > 0) {
      try {

        fs.unlinkSync('../uploads/' + user.avatar);
        user.avatar = null;
        await this.userService.updateUser(user);
      } catch {
      }
    }
  }
}
