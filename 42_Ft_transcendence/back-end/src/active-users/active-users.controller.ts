import { Controller, Delete, Get, Inject, Param, Post, Put, UseGuards } from '@nestjs/common';
import { MessageBody } from '@nestjs/websockets';
import { UserGuard } from 'src/auth/user.guard';
import { ActiveUsersService } from './active-users.service';

@Controller('active-users')
export class ActiveUsersController {
    constructor(@Inject('ACTIVE_USERS_SERVICE') private service: ActiveUsersService) {}

    @Get(':id')
    @UseGuards(UserGuard)
    async getUsersInChat(@Param('id') id: string) {
        return await this.service.getUsersByChatId(id);
    }

    @Delete()
    @UseGuards(UserGuard)
    async removeUserFromChat(@MessageBody() data: any)
    {
        return await this.service.removeUserByUserId(data.user_id);
    }

    @Post()
    @UseGuards(UserGuard)
    async newUser(@MessageBody() data: any) {
        return await this.service.addUser(data);
    }

    @Put()
    @UseGuards(UserGuard)
    async updateUser(@MessageBody() data: any) {
        return await this.service.updateUser(data);
    }
}
