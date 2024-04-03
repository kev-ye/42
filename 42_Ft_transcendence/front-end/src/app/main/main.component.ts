import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Router } from "@angular/router";

import { GlobalConsts } from '../common/global';
import { DataSharedService } from "../service/data/data-shared.service";


interface UserEntity {
	id: number;
	name: string;
	login: string;
	avatar: string;
	fortyTwoAvatar: string;
	created: string;
	online: boolean;
	twoFactorQR: string;
	twoFactorSecret: string;
}

interface GameEntity {
	id: string;
	created: Date;
	first: string;
	second: string;
	first_user: string;
	second_user: string;
	first_score: number;
	second_score: number;
	limit_game: number;
	game_state: number;
	power: number;
	creator_id: string;
	first_user_obj: UserEntity;
	second_user_obj: UserEntity;
}


@Component({
	selector: 'app-main',
	templateUrl: './main.component.html',
	styleUrls: ['./main.component.css']
})
export class MainComponent implements OnInit {
	user: any;
	games: Array<GameEntity>;

	constructor(private data: DataSharedService, private http: HttpClient) { }

	ngOnInit() {
		Promise.resolve(null).then(() => this.data.changeIsLoginData(true));

		this.http.get(`${GlobalConsts.userApi}/user/id/`, { withCredentials: true })
			.subscribe((user: any) => this.user = user );

		// get all games played
		setTimeout(() => {
			
			this.http.get('/pongApi/game/', { withCredentials: true }).subscribe((games: any) => {
	
				if (!games || !this.user)
					return;
	
				this.games = games.filter((game: GameEntity) => game.game_state == 2 && (game.first_user === this.user.id) || game.second_user == this.user.id);
	
				// get users for each game
				for (let game of this.games) {
					this.http.get(`${GlobalConsts.userApi}/user/id/` + game.first_user, { withCredentials: true })
						.subscribe((user: any) => game.first_user_obj = user );
	
					this.http.get(`${GlobalConsts.userApi}/user/id/` + game.second_user, { withCredentials: true })
						.subscribe((user: any) => game.second_user_obj = user );
				}
			});
		}, 500);
	}
}
