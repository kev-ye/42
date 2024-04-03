import {
  Controller,
  Delete,
  Get,
  Inject,
  Param,
  Patch,
  Post,
  Put,
  Req,
  Res,
  Headers,
  UseGuards
} from '@nestjs/common';
import { MessageBody } from '@nestjs/websockets';
import { Response } from 'express';
import { UserGuard } from 'src/auth/user.guard';
import { ModeratorService } from 'src/moderator/moderator.service';
import { ChannelsService } from './channels.service';

@Controller('channels')
export class ChannelsController {
  constructor(@Inject('CHANNELS_SERVICE') private service: ChannelsService, private modService: ModeratorService) {}
  //@Inject('CHAT_HISTORY_SERVICE') private historyService: ChatHistoryService) {}

  @Get('access/:chatID')
  @UseGuards(UserGuard)
  async checkAccess(
    @Req() req: any,
    @MessageBody() data: any,
    @Param('chatID') chatID: string,
  ) {
    const userID = req.session.userId;
    if (!userID) return false;
    return await this.service.checkAccess(userID, chatID);
  }

  @Get('history/:id')
  @UseGuards(UserGuard)
  async getHistory(@Param('id') id: string, @Headers() headers: any, @Res() res: Response) {
    const tmp = await this.service.getHistory(id, headers['password']);
    

    if (typeof(tmp) == 'boolean')
    {
      res.status(403).send();
      return;
    }
    else
    {
      res.send(tmp);
      return tmp;
    }
  }

  @Get(':id')
  @UseGuards(UserGuard)
  async getChannel(@Param('id') id: string, @Req() req: any) {
    const user = req.session.userId;
    const tmp = await this.service.getChannelById(id);
    let res: any = {};
    if (tmp)
    {
      res = {...tmp};
      if (tmp.creator_id == user)
        res.creator = true;
      if (await this.modService.isModerator(id, user))
        res.moderator = true;
      return res;
    }
    return null;
  }

  @Get()
  @UseGuards(UserGuard)
  async getChannels(@Req() req: any) {
    const userID = req.session.userId;

    return await this.service.getAll(userID);
  }

  @Post('password/:chatID')
  @UseGuards(UserGuard)
  async checkPassword(
    @Param('chatID') chatID: string,
    @MessageBody() data: any,
  ) {
    return await this.service.checkPassword(data.password, chatID);
  }

  @Get('ban/:id')
  @UseGuards(UserGuard)
  async getBanByChat(@Param('id') id: string) {
    return await this.service.getBanByChat(id);
  }

  @Post('ban')
  @UseGuards(UserGuard)
  async banUser(@Req() req: any, @MessageBody() data: any) {
    const userID = req.session.userId;

    return await this.service.banUser(userID, data);
  }

  @Patch('ban')
  @UseGuards(UserGuard)
  async unbanUser(@Req() req: any, @MessageBody() data: any) {
    return await this.service.deleteBan(req.session.userId, data);
  }

  @Post('mute')
  @UseGuards(UserGuard)
  async createMute(@MessageBody() data: any, @Req() req: any) {

    const date = new Date();
    const userID = req.session.userId;

    let tmp: number = +data.seconds;
    tmp += date.getSeconds();
    date.setSeconds(tmp);

    return await this.service.createMute(userID, {
      user_id: data.user_id,
      chat_id: data.chat_id,
      date: date,
    });
  }

  @Post('moderator')
  @UseGuards(UserGuard)
  async createModerator(@MessageBody() data: any, @Req() req: any) {
    const userID = req.session.userId;

    return await this.service.createModerator(userID, data);
  }

  @Patch('moderator')
  @UseGuards(UserGuard)
  async deleteModerator(@MessageBody() data: any, @Req() req: any, @Res() res: Response) {
    const userID = req.session.userId;

    const tmp = await this.service.deleteModerator(userID, data);
    if (tmp)
      res.status(200).send();
    else
      res.status(403).send();
  }

  @Post('invite/name')
  @UseGuards(UserGuard)
  async inviteToChannel(@MessageBody() data: any, @Req() req: any) {
    const userID = req.session.userId;
    const res = await this.service.inviteToChannelByName(userID, data.name, data);
    return res;
  }

  @Post()
  @UseGuards(UserGuard)
  async createChannel(
    @MessageBody() data: any,
    @Req() req: any,
    @Res() res: Response,
  ) {
    const userID = req.session.userId;

    if (!data.name || !/^[a-zA-Z]{6,16}$/.test(data.name))
    {
      res.status(403).send();
      return ;
    }

    if (await this.service.getChannelByName(data.name)) {
      res.status(403).send();
      return;
    }

    const tmp = await this.service.createChannel(userID, data);
    res.status(201).send(tmp);
  }

  @Put()
  @UseGuards(UserGuard)
  async updateChannel(@MessageBody() data: any, @Req() req: any) {
    const userID = req.session.userId;

    return await this.service.updateById(userID, data);
  }

  @Delete()
  @UseGuards(UserGuard)
  async deleteChannel(@MessageBody() data: any) {
    //check if user is owner
    //this.historyService.deleteByChatID(data.chat_id);
  }
}
