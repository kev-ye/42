import { Controller, Get, Inject, Param, Post, Req, UseGuards } from '@nestjs/common';
import { ConnectedSocket, MessageBody } from '@nestjs/websockets';
import { Socket } from 'dgram';
import { UserGuard } from 'src/auth/user.guard';
import { BlockService } from './block.service';

@Controller()
export class BlockController {
    constructor(@Inject('BLOCK_SERVICE') private service: BlockService) {}

    @Post('block')
    @UseGuards(UserGuard)
    async blockUser(@MessageBody() data, @ConnectedSocket() client: Socket, @Req() req: any) {
        if (!data.first || !data.second || data.first == data.second || req.session.userId != data.first)
            return ;
        this.service.blockUser(data);
        return ;
    }

    @Post('unblock')
    @UseGuards(UserGuard)
    async unblockUser(@MessageBody() data, @ConnectedSocket() client: Socket, @Req() req: any) {
        if (!data.first || !data.second || data.first == data.second || req.session.userId != data.first)
            return ;
        this.service.unblockUser(data);
        return ;
    }

    @Get('block/:id')
    @UseGuards(UserGuard)
    async getList(@Param('id') id: number) {
        return this.service.getList(id);
    }
}