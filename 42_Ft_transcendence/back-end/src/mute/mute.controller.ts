import { Controller, Get, Inject, Param, Post, Req, UseGuards } from '@nestjs/common';
import { MessageBody } from '@nestjs/websockets';
import { UserGuard } from 'src/auth/user.guard';
import { MuteService } from './mute.service';

@Controller('mute')
export class MuteController {
    constructor(@Inject('MUTE_SERVICE') private service: MuteService) {}

    @Post()
    @UseGuards(UserGuard)
    async createMute(@MessageBody() data: any, @Req() req: any) {
        let date = new Date();
        
        let tmp: number = +data.seconds;
        tmp += date.getSeconds();
        
        
        date.setSeconds(tmp)
        


        return await this.service.addMute({user_id: data.user_id, chat_id: data.chat_id, date: date}); 
    }
 
    @Get(':chatID/:userID')
    @UseGuards(UserGuard)
    async getMute(@Param('chatID') chatID: string, @Param('userID') userID: string) {
        return await this.service.getMute(chatID, userID); 
    }

    
}
