import { Component, OnInit } from '@angular/core';
import { Router } from "@angular/router";

@Component({
	selector: 'app-game-room',
	templateUrl: './game-room.component.html',
	styleUrls: ['./game-room.component.css']
})
export class GameRoomComponent implements OnInit {

	constructor(private router: Router) { }

	ngOnInit(): void {
	}

	matchMaking(): any {
		this.router.navigate(['match-making'])
	}

	gameSpectator(): any {
		this.router.navigate(['spec_room'])
	}
}
