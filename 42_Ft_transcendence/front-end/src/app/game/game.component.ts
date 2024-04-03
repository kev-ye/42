import { HttpClient } from '@angular/common/http';
import { Component, HostListener, OnDestroy, OnInit } from '@angular/core';
import { io, Socket } from 'socket.io-client';
import { GlobalConsts } from '../common/global';
import { UserApiService } from '../service/user_api/user-api.service';
import { Subscription } from "rxjs";
import { ActivatedRoute, Params, Router } from '@angular/router';
import { MatDialog } from '@angular/material/dialog';
import { DialogError } from './dialogs/error.component';

@Component({
	selector: 'app-game',
	templateUrl: './game.component.svg',
	styleUrls: ['./game.component.css']
})
export class GameComponent implements OnInit, OnDestroy {

	private user: any;
	private subscription: Subscription = new Subscription();
	private leftPage: boolean = false;
	gameColor = 'rgb(20, 20, 20)';
	movablesColor = 'rgb(255, 255, 255)'

	public socket: Socket;
	gameID: string;
	first_name: string = '';
	second_name: string = '';

	game = {
		WIDTH: 100,
		HEIGHT: 100
	}

	paddle = {
		WIDTH: 1,
		HEIGHT: 20,
		PADDING: 4,
		RADIUS: 3,
		SPEED: 3
	}

	ball_t = {
		RADIUS: 1,
		SPEED: 1,
		X: 50,
		Y: 50
	}

	ball = {
		x: this.ball_t.X,
		y: this.ball_t.Y,
		xIncrement: 0,
		yIncrement: 0,
	}

	player1 = {
		score: 0,
		x: this.paddle.PADDING,
		y: (this.game.HEIGHT / 2) - (this.paddle.HEIGHT / 2)
	}

	player2 = {
		score: 0,
		x: this.game.WIDTH - this.paddle.WIDTH - this.paddle.PADDING,
		y: (this.game.HEIGHT / 2) - (this.paddle.HEIGHT / 2)
	}

	power : any = null;

	constructor(private http: HttpClient, private userApi: UserApiService,
		private route: ActivatedRoute, private dialog: MatDialog,
		private router: Router) {
		// this.start()
	}

	async sleep(ms: number) {
		return new Promise((r) => setTimeout(r, ms));
	  }

	showError(error: string, redirect: boolean = true) {
		const tmp = this.dialog.open(DialogError, {
			data: {
				error: error
			}
		});
		if (redirect)
			tmp.afterClosed().subscribe(() => {
				this.router.navigate(['game_room']);
			})
		return tmp;
	}

	initSocket() {

		this.route.queryParams.subscribe((data: any) => {
			if (data.id)
			{
				this.socket.emit('connectGame', {game_id: data.id})
			}
			else if (data.spec)
			{
				this.socket.emit('spectate', {game_id: data.spec});
			}
			else
			{
				const tmp = this.showError('Waiting for game', false);
				setTimeout(() => {
					this.socket.emit('startMatchmaking');
				}, 500);

				this.socket.on('joinedGame', (data) => {
					if (data.game_id)
					{
						this.gameID = data.game_id;
						tmp.close();
						this.first_name = data.first;
						this.second_name = data.second;
					}
					else
					{
					}
				})
			}
		})

		this.socket.on('error', (data: any) => {
			if (!data.error)
				return;
			this.leftPage = true;
			this.showError(data.error);
		});

		this.socket.on('refresh', (data: any) => {			
			this.ball.x = data[0].pos.x + 50;
			this.ball.y = data[0].pos.y + 50;
			this.player1.score = data[0].score.first;
			this.player2.score = data[0].score.second;
			this.player1.y = data[0].first + 50 - this.paddle.HEIGHT / 2;
			this.player2.y = data[0].second + 50 - this.paddle.HEIGHT / 2;
			this.power = data[0].power;
			if (this.power)
			{
				this.power.pos.x += 50;
				this.power.pos.y += 50;
			}
			
			
		});

		this.socket.on('win', (data: any) => {
			this.showError(data.username + ' wins the game !');
		})

		this.socket.on('joinedGame', (data: any) => {
			this.gameID = data.game_id;
			this.first_name = data.first;
			this.second_name = data.second;
		})

		this.subscription.add(this.userApi.getUser().subscribe({
			next: (data) => {
				this.user = { ...data }
			},
		}));
	}


	ngOnInit() : void {
		this.socket = io(`ws://localhost:3002/${GlobalConsts.gameSockIo}`, {
			path: `/${GlobalConsts.gameSockIo}/socket.io`,
			withCredentials: true,
			closeOnBeforeunload: true,
			reconnection: false,
			transports: ['websocket'],
			autoConnect: true,
			timeout: 3000
		}).on('connect', () => {
			this.socket.on('user', () => {
				this.http.get(`${GlobalConsts.userApi}/user/id`).subscribe(async (data: any) => {
					this.socket.emit('user', {id: data.id});
					await this.sleep(500);
					this.initSocket();
				})
			});
		});

		setTimeout(() => {
			if (this.socket.disconnected && !this.leftPage)
			{
				this.showError('Could not connect to game server');
			}
		}, 1000);


	}

	ngOnDestroy(): void {
		this.socket.disconnect();
		this.leftPage = true;
	}

	stopSocket() {
		this.socket.disconnect();
	}

	resetBall() : void {

	}


	startMatchmaking() {
		this.socket.emit('startMatchmaking')
	}

	@HostListener("window:keydown", ["$event"])
	onKeyDown(e: any) {
		let threshold: number = 0
		if (this.socket.disconnected)
			return ;

		if (e.code === "ArrowUp") {
			e.preventDefault();
			threshold = -this.paddle.SPEED
		}
		else if (e.code === "ArrowDown") {
			e.preventDefault();
			threshold = this.paddle.SPEED
		}
		else
			return;

		/* animation was too slow - had to do this trick */
		let val: number = threshold < 0 ? -1 : 1
		this.socket.emit('input', {value: val, game_id: this.gameID});


		// window.requestAnimationFrame(() => this.movePaddle(threshold));
	}

	movePaddle(val: number) : void {
	}

	goalCollision(x: number) {

	}

	wallCollision(y: number) {
	}

	paddleCollision(x: number, y: number) {
	}

	moveBall() : void {

	}

	changeColor(): void {
		const r = Math.floor(Math.random() * 256);
		const g = Math.floor(Math.random() * 256);
		const b = Math.floor(Math.random() * 256);
		this.gameColor = `rgb(${r}, ${g}, ${b})`;

		// revert ball & paddles color if the background color is too bright / dark
		if (r > 200 || g > 200 || b > 200)
			this.movablesColor = "rgb(30, 30, 30)";
		else
			this.movablesColor = "rgb(255, 255, 255)";
	}
}
