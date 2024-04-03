import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { UserLoginComponent } from './user-login/user-login.component';
import { UserSubscriptionComponent } from './user-subscription/user-subscription.component';
import { CombinedGuard } from "./service/guard/combined.guard";
import { AuthGuard } from './service/guard/auth.guard';
import { LoginGuard } from "./service/guard/login.guard";
import { IsLoginGuard } from "./service/guard/is-login.guard";
import { TwoFactorGuard } from "./service/guard/two-factor.guard";
import { SubscriptionGuard } from "./service/guard/subscription.guard";
import { MainComponent } from './main/main.component';
import { TwoFactorComponent } from './two-factor/two-factor.component';
import { GameRoomComponent } from "./game-room/game-room.component";
import { GameComponent } from "./game/game.component";
import { MatchMakingComponent } from "./match-making/match-making.component";
import { SpectateRoom } from './spectate-room/spectate-room.component';

const routes: Routes = [
	{ path: '', redirectTo: 'user_login', pathMatch: 'full' },
  	{ path: 'user_login', component: UserLoginComponent, canActivate: [LoginGuard] },
	{ path: 'two_factor', component: TwoFactorComponent, canActivate: [CombinedGuard], data: {
		guards: [IsLoginGuard, TwoFactorGuard]
	}},
  	{ path: 'user_subscription', component: UserSubscriptionComponent, canActivate: [CombinedGuard], data: {
		guards: [IsLoginGuard, SubscriptionGuard]
	}},
	{ path: 'main', component: MainComponent, canActivate: [CombinedGuard], data: {
		guards: [IsLoginGuard, AuthGuard]
	}},
	{ path: 'play', component: GameComponent, canActivate: [IsLoginGuard] },  // need game guard
	{ path: 'game_room', component: GameRoomComponent, canActivate: [IsLoginGuard] }, // need room guard
	{ path: 'match-making', component: MatchMakingComponent, canActivate: [IsLoginGuard] }, // need match-making guard
	{ path: 'spec_room', component: SpectateRoom, canActivate: [IsLoginGuard]},
	{ path: '**', redirectTo: 'user_login', pathMatch: 'full' }
];

@NgModule({
	imports: [
		RouterModule.forRoot(routes)
	],
	exports: [RouterModule]
})
export class AppRoutingModule { }
