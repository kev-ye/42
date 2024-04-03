import { Controller, Get, Inject, Param, Patch, Post, Req, Res, UseGuards } from '@nestjs/common';
import { FriendService } from './friend.service';
import { MessageBody } from '@nestjs/websockets';
import { Interval } from '@nestjs/schedule';
import { Response } from 'express';
import { UserGuard } from 'src/auth/user.guard';

@Controller('friend')
export class FriendController {
  constructor(@Inject('FRIEND_SERVICE') private service: FriendService) {}

  @Post()
  @UseGuards(UserGuard)
  async addFriend(@MessageBody() data: { first: string; second: string }, @Res() res: Response, @Req() req: any) {
    if (req.session.userId != data.first || data.first == data.second)    
    {
      res.status(403).send('Could not add user');
      return;
    }
    const tmp = await this.service.addFriend(data);
    
    if (!tmp)
      res.status(403).send('Could not add user');
    else
      res.status(200).send();
  }

  @Patch()
  @UseGuards(UserGuard)
  async deleteFriend(@MessageBody() data: { first: number; second: number }, @Req() req: any) {
    if (req.session.userId != data.first && req.session.userId != data.second)
      return;
    return await this.service.deleteFriend(data);
  }

  @Get(':id')
  @UseGuards(UserGuard)
  async getFriends(@Param('id') id: string) {
    return await this.service.getFriends(id);
  }
}
