import { Controller, Get, Inject, Param, Post, Req, Res, UseGuards } from '@nestjs/common';
import { GameService } from './game.service';
import { UserGuard } from '../auth/user.guard';
import { UserService } from '../user/user.service'
import e, { Response } from 'express';
import { MessageBody } from '@nestjs/websockets';
import { PlayersService } from 'src/players/players.service';

@Controller('game')
export class GameController {
    constructor(private service: GameService,
        @Inject('USER_SERVICE') private userService: UserService,
        private playerService: PlayersService) {}
        
        @Get()
        @UseGuards(UserGuard)
        async getGames() {
            return await this.service.getAllGames();
        }

        @Post('custom')
        @UseGuards(UserGuard)
        async createCustomGame(@Req() req: any, @Res() res: Response, @MessageBody() data: {limit_game?: number, power?: number}) {
            const userID = req.session.userId;
            
            if (!(await this.userService.getUserById(userID)))
            {
                res.status(403).send();
                return ;
            }
            const player = await this.playerService.getPlayerByUserId(userID);
            let game;
            if (!player)
            {
                res.status(403).send({error: 'Could not find user'});
                return ;
            }
            if ((game = player.find(val => val.game_id)))
            {
                res.send({id: game.game_id, join: false});
                return ;
            }
            let obj: any = {};
            
            if (data.limit_game)
                obj.limit_game = +data.limit_game;
            if (data.power != undefined)
                obj.power = +data.power;
            const newGame = (await this.service.createGameWithCreator(userID, obj));
            res.send({id: newGame.id, join: true});
            setTimeout(async () => {
                const tmp = await this.service.getGameById(newGame.id);
                if (tmp && tmp.first == null)
                    this.service.deleteGameById(newGame.id);
            }, 5000);
            return ;
        }

        @Get('custom/:id')
        @UseGuards(UserGuard)
        async getCustomGameById(@Param('id') id: string) {
            const tmp = await this.service.getGameById(id);
            if (tmp && tmp.creator_id)
                return tmp;
            return null;
        }
    }
    