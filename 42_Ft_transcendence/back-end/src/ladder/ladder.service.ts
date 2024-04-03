import { Inject, Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { LadderEntity } from './entity/ladder.entity';
import { Repository } from 'typeorm';
export const INITIAL_POINTS = 500;
export const POINTS_WINNING = 10;
export const POINTS_LOSING = 10;

@Injectable()
export class LadderService {
    constructor(@InjectRepository(LadderEntity) private ladderRepo: Repository<LadderEntity>) {}

    async getPointsFromUser(user_id: string) {
        return await this.ladderRepo.findOne({id: user_id})
    }

    async createLadderUser(id: string) {
        if (await this.ladderRepo.findOne({id: id}))
            return false; //User is already registered in ladder table
        const tmp = this.ladderRepo.create({id: id, points: INITIAL_POINTS, gamesPlayed: 0});
        await this.ladderRepo.save(tmp);
        return true;
    }

    async UserWins(id: string) {
        let tmp = await this.ladderRepo.findOne({id: id});
        if (!tmp)
            return false; //Can't find user in ladder table
        tmp.gamesPlayed++;
        tmp.win++;
        tmp.points += POINTS_WINNING;        
        await this.ladderRepo.update({id: id}, {gamesPlayed: tmp.gamesPlayed, points: tmp.points, win: tmp.win});
    }

    async UserLoses(id: string) {
        let tmp = await this.ladderRepo.findOne({id: id});
        if (!tmp)
            return false; //Can't find user in ladder table
        tmp.gamesPlayed++;
        tmp.points -= POINTS_LOSING;
        if (tmp.points < 0)
            tmp.points = 0;
        await this.ladderRepo.update({id: id}, {gamesPlayed: tmp.gamesPlayed, points: tmp.points, win: tmp.win});
    }
}
