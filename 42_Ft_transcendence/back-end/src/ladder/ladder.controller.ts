import { Controller, Get, Inject, Param, UseGuards } from '@nestjs/common';
import { UserGuard } from 'src/auth/user.guard';
import { LadderService } from './ladder.service';

export const INITIAL_POINTS = 500;

@Controller('ladder')
export class LadderController {
    constructor(@Inject('LADDER_SERVICE') private ladder: LadderService) {}

    @Get(':id')
    @UseGuards(UserGuard)
    async getLadderById(@Param('id') id: string) {
        const tmp = await this.ladder.getPointsFromUser(id);
        if (tmp)
            return tmp;
        return {id: id, gamesPlayed: 0, points: INITIAL_POINTS, win: 0}
    }

}
