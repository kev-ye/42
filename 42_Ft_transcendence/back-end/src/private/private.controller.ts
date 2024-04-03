import { Controller, Get, Inject, Param, Req, UseGuards } from '@nestjs/common';
import { UserGuard } from 'src/auth/user.guard';
import { PrivateService } from './private.service';

@Controller('private')
export class PrivateController {
    constructor(@Inject('PRIVATE_SERVICE') private service: PrivateService) {}

    @Get(':from/:to')
    @UseGuards(UserGuard)
    async getPrivateMessages(@Param('from') from: string, @Param('to') to: string, @Req() req: any) {
        const userID = req.session.userId;

        if (userID != from && userID != to)
            return ;
        return await this.service.getMessages({first: from, second: to});
    }
}
