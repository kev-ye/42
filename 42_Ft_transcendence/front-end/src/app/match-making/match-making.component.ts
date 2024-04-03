import { Component, OnInit } from '@angular/core';
import { Router } from "@angular/router";
import { HttpClient } from '@angular/common/http';
import { GlobalPositionStrategy } from '@angular/cdk/overlay';
import { GlobalConsts } from '../common/global';

@Component({
	selector: 'app-match-making',
	templateUrl: './match-making.component.html',
	styleUrls: ['./match-making.component.css']
})
export class MatchMakingComponent implements OnInit {

	constructor(private router: Router, private http: HttpClient) { }

	ngOnInit(): void {
	}

	getToGameRoom(): any {
		this.router.navigate(['game_room']).then();
	}

	matchMaking(value: any, power_ups: any): any {
		
		this.http.post(`/${GlobalConsts.userApi}/game/custom`, { limit_game: value, power: power_ups === true ? 6 : 0 }).subscribe((res: any) => {
			if (res && res.id) {
				this.router.navigate(['play'], {
					queryParams: {
						id: res.id
					}
				})
			}
		});
	}

	joinGame(id: string) {
		this.router.navigate(['play'], {
			queryParams: {
				id: id
			}
		});
	}

	startMatchmaking() {
		this.router.navigate(['play']);
	}
}
