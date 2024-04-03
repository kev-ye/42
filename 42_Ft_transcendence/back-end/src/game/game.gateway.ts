import { Inject, OnModuleInit } from '@nestjs/common';
import { Interval } from '@nestjs/schedule';
import {
  ConnectedSocket,
  MessageBody,
  OnGatewayConnection,
  OnGatewayDisconnect,
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets';
import { stat } from 'fs';
import { first } from 'rxjs';
import { RemoteSocket, Server, Socket } from 'socket.io';
import { DefaultEventsMap } from 'socket.io/dist/typed-events';
import { LadderService } from 'src/ladder/ladder.service';
import { PlayersService } from 'src/players/players.service';
import { UserService } from 'src/user/user.service';
import { GameService } from './game.service';
export const TIME_TO_REFRESH = 20; //milliseconds
export const XSPEED_MIN = 0.5;
export const YSPEED_MIN = 0.5;
export const MAX_SPEED = 1;
export const PERCENTAGE_POWER = 0.3;

@WebSocketGateway(3002, {
  path: '/gameSockIo/socket.io',
  namespace: 'gameSockIo',
  cors: {
    origin: [
      'http://localhost',
      'http://localhost:80',
      'http://localhost:4200',
    ],
    methods: ['GET', 'POST'],
    credentials: true,
  },
  transports: ['websocket'],
})
export class GameGateway implements OnGatewayConnection, OnGatewayDisconnect {
  constructor(
    private playerService: PlayersService,
    private service: GameService,
    @Inject('USER_SERVICE') private userService: UserService,
    @Inject('LADDER_SERVICE') private ladder: LadderService
  ) {}

  game = {
		WIDTH:  100,
		HEIGHT: 100
	}

	paddle = {
		WIDTH:   1,
		HEIGHT:  20,
		PADDING: 4,
		RADIUS:  3,
		SPEED:   3
	}

	ball_t = {
		RADIUS: 1,
		SPEED:  1,
		X:      50,
		Y:      50
	}

  @WebSocketServer() 
  server: Server;

  stats: Map<string, any> = new Map();

  async sleep(ms: number) {
    return new Promise((r) => setTimeout(r, ms));
  }

  async emitUser(userID: string, event: string, ...args: any[]) {
    const tmp = await this.playerService.getPlayerByUserId(userID);
    if (tmp.length > 0) {
      await this.server.fetchSockets().then(data => {
        for (const it of tmp) {
          const sock = data.find(val => val.id == it.socket_id);
          if (sock)
            sock.emit(event, args);
        }
      });
    }
  }

  async getSocket(socketID: string): Promise<any> {
    let res: RemoteSocket<DefaultEventsMap, any> = null;
    await this.server.fetchSockets().then(data => {
      const sock = data.find(val => val.id == socketID);
      if (sock)
        res = sock;
    });
    return res;
  }

  emitRoom(room: string, event: string, ...args: any[]) {
    this.server.to(room).emit(event, args);
  }

  async handleConnection(client: any, ...args: any[]) {
    await this.playerService.createPlayer(client.id);

    client.emit('user');
    //client must send his user details when he receives this signal
  }

  async checkForfeit(client: Socket) {
    const player = await this.playerService.getPlayerBySocketId(client.id);
    
    if (!player || !player.game_id || !player.user_id) return;
    const user = await this.userService.getUserById(player.user_id);

    if (!user) return;
    const game = await this.service.getGameById(player.game_id);

    if (game) {
      if (game.game_state == 1 && (game.first == client.id || game.second == client.id)) {
        if (game.first == client.id) { //second wins
          const user_2 = await this.userService.getUserById(game.second_user);


          this.playerLoses(game.first_user);
          this.playerWins(game.second_user);
          this.server.to(game.id).emit('win', {username: user_2 ? user_2.name : 'Anonymous'})
          this.stats.set(game.id, {...this.stats.get(game.id), score: {second: game.limit_game, first: 0}});
        }
        else { //first wins
          const user_2 = await this.userService.getUserById(game.first_user);

          this.playerWins(game.first_user);
          this.playerLoses(game.second_user);
          this.server.to(game.id).emit('win', {username: user_2 ? user_2.name : 'Anonymous'})
          this.stats.set(game.id, {...this.stats.get(game.id), score: {first: game.limit_game, second: 0}});
        }
        
        if (this.stats.has(game.id))
          this.stopGame(game.id, this.stats.get(game.id));
        else
          this.stats.delete(game.id);
      }
      else if (game.game_state == 0)
        this.service.deleteGameById(game.id);
    }
  }

  async handleDisconnect(client: Socket) {
    
    await this.checkForfeit(client);
    await this.playerService.deletePlayerBySocketId(client.id);
  }

  //client sends his user details so we update player DB
  @SubscribeMessage('user')
  async updateUser(
    @MessageBody() data: any,
    @ConnectedSocket() client: Socket,
  ) {
    await this.playerService.setUserIdBySocketId(client.id, data.id);
  }

  @SubscribeMessage('connectGame')
  async connectToGame(
    @MessageBody() data: { game_id: string },
    @ConnectedSocket() client: Socket,
  ) {
    const tmp = await this.service.getGameById(data.game_id);
    
    if (!tmp || tmp.game_state == 2) {
      client.emit('error', { error: 'Game was not found' });
      return;
    }
    if (tmp.first && tmp.second) {
      client.emit('error', { error: 'Game is full' });
      return ;
    }
    const player = await this.playerService.getPlayerBySocketId(client.id);
    if (!player || !player.user_id) {
      client.emit('error', { error: 'Could not find user details' });
      return ;
    }
    if ((await this.playerService.getPlayerByUserId(player.user_id)).find(val => val.game_id))
    {
      client.emit('error', {error: 'You are already playing a game'});
      return;
    }
    await this.playerService.updatePlayer({id: player.id}, {status: 0});
    const game = await this.service.joinGame(player, data.game_id);
    if (game)
    {
      client.join(game.id);
    }
    if (game.first && game.second)
      this.startGame(game.id);
    
  }

  @SubscribeMessage('disconnectGame')
  async disconnectFromGame(@ConnectedSocket() client: Socket) {
    //this.handleDisconnect(client);
    //client.disconnect();
  }

  @Interval(3000)
  async checkMatchmaking() {
    const tmp = await this.playerService.getLookingPlayers();
    if (tmp.length < 2) return;
    const game = await this.service.createGame();
    await this.service.joinGame(tmp[0], game.id);
    await this.service.joinGame(tmp[1], game.id);
    await this.playerService.updatePlayer({ id: tmp[0].id }, { status: 2 });
    await this.playerService.updatePlayer({ id: tmp[1].id }, { status: 2 });

    const player_1 = await this.playerService.getPlayerBySocketId(
      tmp[0].socket_id,
    );
    const player_2 = await this.playerService.getPlayerBySocketId(
      tmp[1].socket_id,
    );

    const sock_1 = await this.getSocket(player_1.socket_id);
    if (sock_1) {
      sock_1.join(game.id);
    }

    const sock_2 = await this.getSocket(player_2.socket_id);
    if (sock_2) {
      sock_2.join(game.id);
    }

    this.startGame(game.id);
  }

  @SubscribeMessage('startMatchmaking')
  async joinMatchmaking(@ConnectedSocket() client: Socket) {
    
    let error = false;
    const tmp = await this.playerService.getPlayerBySocketId(client.id);
    

    if (!tmp || !tmp.user_id) return;

    const players = await this.playerService.getLookingPlayers();
    players.forEach((val) => {

        if (val.user_id == tmp.user_id)
          error = true;
          
    });
    if (error)
    {
      client.emit('error', {error: 'User already in queue'});
      return;
    }

    
    await this.playerService.updatePlayer({ id: tmp.id }, { status: 1 });
  }

  @SubscribeMessage('stopMatchmaking')
  async leaveMatchmaking(@ConnectedSocket() client: Socket) {
    const tmp = await this.playerService.getPlayerBySocketId(client.id);

    if (!tmp || !tmp.user_id) return;
    await this.playerService.updatePlayer({ id: tmp.id }, { status: 0 });
  }

  @SubscribeMessage('spectate')
  async spectateGame(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
    if (!data.game_id)
    {
      client.emit('error', {error: 'Could not find game to spectate'});
      return;
    }
    const game = await this.service.getGameById(data.game_id);
    if (!game)
    {
      client.emit('error', {error: 'Could not find game to spectate'});
      return;
    }
    client.join(data.game_id);
  }

  newRound(stats: any) {
    stats.pos.x = 0;
    stats.pos.y = 0;
    stats.speed = this.generateRandomSpeed();
    //stats.first = 0;
    //stats.second = 0;
  }

  async startGame(gameID: string) {
    const game = await this.service.getGameById(gameID);
    if (!game || !game.first_user || !game.second_user || !game.first || !game.second) {
      this.server.to(gameID).emit('error', {error: 'Could not load game, please try again'});
      return ;
    }

    
    this.server.to(gameID).emit('joinedGame', { game_id: gameID, first: (await this.userService.getUserById(game.first_user))?.name, second: (await this.userService.getUserById(game.second_user))?.name });
    //wait 3 seconds to start
    await this.sleep(3000);

    this.service.startGame(gameID);
    this.stats.set(game.id, {
      first: 0, //position of first player
      second: 0, //position of second player
      first_socket: game.first,
      second_socket: game.second,
      speed: this.generateRandomSpeed(), //ball's speed
      pos: {
        //ball's position
        x: 0,
        y: 0,
      },
      power: null, //{
      //   type: 0, //1: speed x2 2: teleportation
      //   pos: {
      //     x: 0,
      //     y: 0,
      //   },
      //},
      score: { first: 0, second: 0 },
    });

    const interval = setInterval(async () => {
      if (!this.stats.has(game.id)) {
        clearInterval(interval);
        return;
      }
      const data = this.stats.get(game.id);


      //moving ball
      data.pos.x += data.speed.x;
      data.pos.y += data.speed.y;
      if (data.pos.y <= -50) {
        //considerer ball radius
        data.pos.y = -50;
        data.speed.y *= -1;
      }
      else if (data.pos.y >= 50)
      {
        data.pos.y = 50;
        data.speed.y *= -1;
      }


      //win check
      if (data.pos.x <= -50) {
        data.speed = this.generateRandomSpeed();
        data.score.second++;
        if (data.score.second >= game.limit_game) {
          this.emitRoom(gameID, 'refresh', data);
          const player_1 = await this.playerService.getPlayerBySocketId(game.first);
          const player_2 = await this.playerService.getPlayerBySocketId(game.second);
          if (!player_1 || !player_2)
            return ;
          const user_1 = await this.userService.getUserById(player_1.user_id);
          const user_2 = await this.userService.getUserById(player_2.user_id);
          this.playerWins(user_2.id);
          this.playerLoses(user_1.id);
          this.server.to(game.id).emit('win', {username: user_2.name});
          this.stopGame(game.id, data);
          clearInterval(interval);
          return;
        }
        this.newRound(data);
      } else if (data.pos.x >= 50) {
        data.speed = this.generateRandomSpeed();
        data.score.first++;
        if (data.score.first >= game.limit_game) {
          this.emitRoom(gameID, 'refresh', data);
          const player_1 = await this.playerService.getPlayerBySocketId(game.first);
          const player_2 = await this.playerService.getPlayerBySocketId(game.second);
          if (!player_1 || !player_2)
            return ;
          const user_1 = await this.userService.getUserById(player_1.user_id);
          const user_2 = await this.userService.getUserById(player_2.user_id);
          this.playerWins(user_1.id);
          this.playerLoses(user_2.id);
          this.server.to(game.id).emit('win', {username: user_1.name});
          this.stopGame(game.id, data);
          clearInterval(interval);
          return;
        }
        this.newRound(data);
      }

      //paddle collision
      if (data.pos.x <= -45 && data.pos.x - data.speed.x > -45 && data.speed.x < 0) {
        if (Math.abs(data.pos.y - data.first) <= this.paddle.HEIGHT / 2) {
          data.pos.x = -45;
          data.speed.x *= -1;
        }
      } else if (data.pos.x >= 45 && data.pos.x - data.speed.x < 45 && data.speed.x > 0) {
        if (Math.abs(data.pos.y - data.second) <= this.paddle.HEIGHT / 2) {
          data.pos.x = 45;
          data.speed.x *= -1;
        }
      }

      if (game.power)
      {
        if (data.power == null)
        {
          //percentage chance on 100 a power spawns
          const tmp = Math.random() * 100;        
          if (tmp > PERCENTAGE_POWER)
          {
            this.emitRoom(gameID, 'refresh', data);
            return ;
          }
          
          data.power = {
            type : 0,
            pos : {
              x: (Math.random() * 50 - 25),
              y: (Math.random() * 50 - 25)
            }
          }
          if (game.power == 2) //speed x2
          data.power.type = 2;
          else if (game.power == 4) //teleportation
          data.power.type = 4;
          else //both
          {
            const yo = Math.random();
            data.power.type = yo < 0.5 ? 2 : 4;
            
          }
        }
        else
        {
          if (Math.sqrt(Math.pow((data.power.pos.x - data.pos.x), 2) + Math.pow((data.power.pos.y - data.pos.y), 2)) <= this.ball_t.RADIUS * 5)
          {
            
            if (data.power.type == 2) //speed * 2
            {
              data.speed.x *= 2;
              data.speed.y *= 2;
            } else if (data.power.type == 4) //teleportation
            {
              data.pos.x = Math.random() * 30 - 15;
              data.pos.y = Math.random() * 30 - 15;
              data.speed = this.generateRandomSpeed();
            }
            data.power = null;
          }

        }
      }        
      this.emitRoom(gameID, 'refresh', data);
    }, TIME_TO_REFRESH);
  }

  async stopGame(gameID: string, data: any) {
    await this.service.stopGame(gameID, data);
    this.stats.delete(gameID);
  }

  generateRandomSpeed(): { x: number; y: number } {
    let x = ((Math.random()) * MAX_SPEED * 2) - MAX_SPEED;
    let y = ((Math.random()) * MAX_SPEED * 2) - MAX_SPEED;

    if (Math.abs(x) < XSPEED_MIN) x = x < 0 ? -XSPEED_MIN : XSPEED_MIN;
    if (Math.abs(y) < YSPEED_MIN) y = y < 0 ? -YSPEED_MIN : YSPEED_MIN;
    return { x: x, y: y };
  }

  @SubscribeMessage('input')
  async inputPlayer(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
    if (!data.game_id)
      return;
    if (!this.stats.has(data.game_id))
      return;
    const tmp = this.stats.get(data.game_id);
    const value = data.value * 5;
    if (tmp.first_socket == client.id)
    {
      if (tmp.first + value < -50 + this.paddle.HEIGHT / 2)
        this.stats.set(data.game_id, {...tmp, first: -50 + this.paddle.HEIGHT / 2});
      else if (tmp.first + value > 50 - this.paddle.HEIGHT / 2)
        this.stats.set(data.game_id, {...tmp, first: 50 - this.paddle.HEIGHT / 2});
      else
        this.stats.set(data.game_id, {...tmp, first: tmp.first + value});
    }
    else if (tmp.second_socket == client.id)
    {
      if (tmp.second + value < -50 + this.paddle.HEIGHT / 2)
        this.stats.set(data.game_id, {...tmp, second: -50 + this.paddle.HEIGHT / 2});
      else if (tmp.second + value > 50 - this.paddle.HEIGHT / 2)
        this.stats.set(data.game_id, {...tmp, second: 50 - this.paddle.HEIGHT / 2});
      else
        this.stats.set(data.game_id, {...tmp, second: tmp.second + value});
    }
  }

  async playerLoses(user_id: string | undefined) {
    if (user_id == undefined)
      return ;
    await this.ladder.createLadderUser(user_id);
    await this.ladder.UserLoses(user_id);
  }

  async playerWins(user_id: string | undefined) {
    if (user_id == undefined)
      return ;
    await this.ladder.createLadderUser(user_id);
    await this.ladder.UserWins(user_id);
  }
}
