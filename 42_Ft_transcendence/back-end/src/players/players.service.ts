import { Injectable, OnModuleDestroy, OnModuleInit } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { PlayerEntity } from './entity/player.entity';

@Injectable()
export class PlayersService implements OnModuleInit {
    constructor(@InjectRepository(PlayerEntity) private repo: Repository<PlayerEntity>) {}

    async onModuleInit() {
        await this.repo.clear();
    }

    async createEmptyPlayer() {
        const tmp = this.repo.create();
        await this.repo.save(tmp);
        return tmp;
    }

    async createPlayer(socketID: string) {
        const tmp = this.repo.create({socket_id: socketID});
        await this.repo.save(tmp);
        return tmp;
    }

    async getPlayerBySocketId(socketID: string | undefined) {
        if (socketID == undefined)
            return null;
        return await this.repo.findOne({socket_id: socketID});
    }

    async getPlayerByUserId(userID: string) {
        return await this.repo.find({user_id: userID});
    }

    async getLookingPlayers() {
        return await this.repo.find({where: {status: 1}});
    }

    async getPlayersInGame(gameID: string) {
        return await this.repo.find({game_id: gameID});
    }

    async setGameID(userID: string, gameID: string) {
        return await this.repo.update({user_id: userID}, {game_id: gameID});
    }

    async deletePlayerByUserId(userID: string) {
        return await this.repo.delete({user_id: userID});
    }

    async deletePlayerById(id: string) {
        return await this.repo.delete({id: id});
    }

    async deletePlayerBySocketId(socketID: string) {
        return await this.repo.delete({socket_id: socketID});
    }

    async setUserIdBySocketId(socketID: string, userID: string) {
        const tmp = this.repo.findOne({socket_id: socketID});
        if (tmp)
            this.repo.update({socket_id: socketID}, {user_id: userID});
    }

    async updatePlayer(criteria: any, data: any) {
        return await this.repo.update(criteria, data);
    }
}
