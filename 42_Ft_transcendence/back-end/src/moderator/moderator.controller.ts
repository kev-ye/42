import { Controller, Delete, Get, Inject, Logger, Param, Patch, Post, Req, UseGuards } from '@nestjs/common';
import { MessageBody } from '@nestjs/websockets';
import { UserGuard } from 'src/auth/user.guard';
import { UserService } from 'src/user/user.service';
import { ModeratorService } from './moderator.service';

@Controller('moderator')
export class ModeratorController {
    constructor(private service: ModeratorService, @Inject('USER_SERVICE') private userService: UserService) {}

    @Get(':chatID')
    @UseGuards(UserGuard)
    async getModerators(@Param('chatID') chatID: string) {
        const tmp = await this.service.getModeratorsByChatID(chatID);
        let result : any[] = [];
        for (let it of tmp)
        {
            const user = await this.userService.getUserById(it.user_id);
            if (user)
                result.push({...it, name: user.name});
        }
        return result;
    }

    @Post()
    @UseGuards(UserGuard)
    async createModerator(@MessageBody() data: any, @Req() req: any) {
        const userID = req.session.userId;

        return await this.service.createModerator(userID, data);
    }

    @Patch()
    @UseGuards(UserGuard)
    async deleteModerator(@MessageBody() data: any, @Req() req: any) {
        const userID = req.session.userId;

        return await this.service.deleteModerator(userID, data);
    }

    @Patch('all')
    @UseGuards(UserGuard)
    async deleteAllModerators(@MessageBody() data: any, @Req() req: any) {
        const userID = req.session.userId;

        return await this.service.deleteAllModerator(data);
    }
}
