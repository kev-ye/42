import { Component, OnInit } from "@angular/core";
import { HttpClient } from '@angular/common/http';
import { Router } from "@angular/router";

import { GlobalConsts } from '../common/global';

@Component({
	templateUrl: './spectate-room.component.html',
	styleUrls: ['./spectate-room.component.css'],
	selector: 'spectate-room'
}) export class SpectateRoom implements OnInit {

	games: Array<any> = [];

	constructor(private router: Router, private http: HttpClient) {
	}

	ngOnInit(): void {
		this.http.get('/pongApi/game/').subscribe((games: any) => {

			if (!games)
				return;

			this.games = games.filter((game: any) => game.game_state === 1);

			for (let game of this.games) {
				this.http.get(`${GlobalConsts.userApi}/user/id/` + game.first_user, { withCredentials: true })
					.subscribe((user: any) => game.first_user_obj = user);

				this.http.get(`${GlobalConsts.userApi}/user/id/` + game.second_user, { withCredentials: true })
					.subscribe((user: any) => game.second_user_obj = user);
			}
		});
	}

	getToGameRoom(): any {
		this.router.navigate(['game_room']).then();
	}

	spectateGame(id: string) {
		if (id == "")
			return;
		this.router.navigate(['play'], { queryParams: { spec: id } });
	}
}
