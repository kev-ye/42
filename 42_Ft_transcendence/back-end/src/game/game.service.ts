import { Injectable, OnModuleInit } from '@nestjs/common';
import { targetModulesByContainer } from '@nestjs/core/router/router-module';
import { Interval } from '@nestjs/schedule';
import { InjectRepository } from '@nestjs/typeorm';
import { WebSocketServer } from '@nestjs/websockets';
import { stat } from 'fs';
import { report } from 'process';
import { Server } from 'socket.io';
import { PlayersService } from 'src/players/players.service';
import { clearInterval } from 'timers';
import { Repository } from 'typeorm';
import { GameEntity } from './entity/game.entity';
import { GameGateway } from './game.gateway';
export const TIME_TO_REFRESH = 200; //milliseconds
export const XSPEED_MIN = 0.1;
export const YSPEED_MIN = 0.1;

@Injectable()
export class GameService implements OnModuleInit {
    constructor(@InjectRepository(GameEntity) private repo: Repository<GameEntity>,
    private playerService: PlayersService) {}

    onModuleInit() {
        this.repo.delete({game_state: 0});
        this.repo.delete({game_state: 1});

    }

    async getAllGames() {
        return await this.repo.find({order: {created: "DESC"}});
    }

    @WebSocketServer()
    server: Server;

    async startGame(gameID: string) {
        await this.repo.update({id: gameID}, {game_state: 1});
    }

    async updateGameById(id: string, data: any) {
        return await this.repo.update({id: id}, data);
    }

    async getGameById(id: string) {
        const tmp = await this.repo.find();
        for (let it of tmp)
        {
            if (it.id == id)
                return it;
        }
        return null;
    }

    async getGameByCreator(creator_id: string) {
        return await this.repo.find({creator_id: creator_id});
    }

    async getGameByStatus(status: number) {
        return await this.repo.find({game_state: status});
    }

    async createGame(): Promise<GameEntity> {
        const tmp = this.repo.create();
        return await this.repo.save(tmp);
    }

    async createGameWithCreator(userID: string, data?: any) {
        let tmp;
        
        if (data)
            tmp = this.repo.create({creator_id: userID, ...data});
        else
        tmp = this.repo.create({creator_id: userID});
        return await this.repo.save(tmp);
    } 

    async deleteGameById(id: string) {
        return await this.repo.delete({id: id});
    }

    async joinGame(player: any, gameID: string) {
        
        if (player == undefined)
            return null;
        const tmp = await this.repo.findOne({id: gameID});
        if (tmp)
        {
            if (!tmp.first)
            {
                tmp.first = player.socket_id;
                tmp.first_user = player.user_id;
            }
            else if (!tmp.second && player.socket_id != tmp.first)
            {
                tmp.second = player.socket_id;
                tmp.second_user = player.user_id;
            }
            else
                return null;            
            await this.playerService.updatePlayer({socket_id: player.socket_id}, {game_id: gameID});
            await this.repo.update({id: tmp.id}, tmp);
            return tmp;
        }
        return null;
    }

    async handleDisconnect(socketID: string) {
    }

    async forfeitGame(socketID: string, gameID: string) {

    }

    async stopGame(gameID: string, data: any) { //save game data
        const tmp = await this.repo.findOne({id: gameID});
        if (tmp) {
            await this.repo.update(tmp.id, {
                first: data.first_socket,
                second: data.second_socket,
                first_score: data.score.first,
                second_score: data.score.second,
                game_state: 2
            });
            const players = await this.playerService.getPlayersInGame(tmp.id);
            players.forEach(val => {
                this.playerService.updatePlayer({id: val.id}, {status: 0, game_id: null});
            });
        }
        return false;
    }
}