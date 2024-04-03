import { HttpClient } from '@angular/common/http';
import { Component, EventEmitter, OnInit, Output } from '@angular/core';
import { MatDialog } from '@angular/material/dialog';
import { GlobalConsts } from '../common/global';
import { Router } from '@angular/router';
import { UserApiService } from '../service/user_api/user-api.service';
import { UserAuthService } from '../service/user_auth/user-auth.service';
import { Subscription } from "rxjs";
import { DialogChangeImage } from './dialogs/dialog-change-image.component';
import { DialogChangeUsername } from './dialogs/dialog-change-username.component';
import { DataSharedService } from "../service/data/data-shared.service";


@Component({
	selector: 'app-user',
	templateUrl: './user.component.html',
	styleUrls: ['./user.component.css']
})
export class UserComponent implements OnInit {
	private subscription: Subscription = new Subscription();

	user: any;

	changeUsername: boolean = false;
	connected: boolean = false;

	twoFaActive: boolean = false;
	qrCode: string = '';

	isLogin: boolean = true;
	@Output() closeEmitter = new EventEmitter<boolean>()

	constructor(public dialog: MatDialog,
		private http: HttpClient,
		private router: Router,
		private userApi: UserApiService,
		private userAuth: UserAuthService,
		private data: DataSharedService) { }

	refreshUserDetails() {
		//load data from backend server

		this.http.get(`${GlobalConsts.userApi}/user/id/`, { withCredentials: true }).subscribe({
			next: data => {
				if (!data) {
					return;
				}
				const tmp = data as any;
				this.user = tmp;
				this.user.username = tmp.name;
				this.user.avatar = `${GlobalConsts.userApi}/image/user/` + this.user.id + `?random=${Math.random()}`;

				this.connected = true;

				this.http.get(`${GlobalConsts.userApi}/ladder/` + this.user.id, { withCredentials: true }).subscribe({
					next: (data: any) => {
						this.user = { ...this.user, ladder: data.points, gamesPlayed: data.gamesPlayed, win: data.win }
					},
					error: data => {

					}
				});
			}, error: data => {

			}
		});
	}

	ngOnInit(): void {
		this.subscription.add(this.data.isLoginData.subscribe(data => this.isLogin = data));

		if (this.isLogin) {
			this.refreshUserDetails();
			this.subscription.add(this.userApi.getUser().subscribe({
				next: (v) => {
					if (v.twoFactorSecret) {
						this.twoFaActive = true;
						this.qrCode = v.twoFactorQR;
					}
				},
			}))
		}
	}

	ngOnDestroy() {
		this.subscription.unsubscribe();
	}

	openImageDialog() {
		const tmp = this.dialog.open(DialogChangeImage, {
			data: {
				user_id: this.user.id
				// data
			}
		});
		tmp.afterClosed().subscribe(data => {
			this.user.avatar = `${GlobalConsts.userApi}/image/user/` + this.user.id + `?random=${Math.random()}`;
		});
	}

	openUsername() {
		if (this.changeUsername)
			this.changeUsername = false;
		else
			this.changeUsername = true;
		const ref = this.dialog.open(DialogChangeUsername, {
			data: {
				id: this.user.id
			} //change data to send to dialog
		});
		ref.afterClosed().subscribe(data => {
			if (data == true)
				this.refreshUserDetails();
		})
	}

	turnOnTwoFa() {
		this.subscription.add(this.userAuth.twoFaGenerate().subscribe({
			next: (v) => {
				this.qrCode = v.qr;
				this.twoFaActive = true;
			},
			error: (e) => {
				alert('Something wrong, try again!');
			},
		}));
	}

	turnOffTwoFa() {
		this.subscription.add(this.userAuth.twoFaTurnOff().subscribe({
			next: _ => {
				this.qrCode = '';
				this.twoFaActive = false;
			},
			error: (e) => {
				alert('Something wrong, try again!');
			},
		}));
	}

	logOut(): void {
		const confirm$: boolean = confirm('Are you sure?');
		if (confirm$) {
			this.subscription.add(this.userAuth.logout().subscribe({
				next: _ => {
					this.data.changeIsLoginData(false);
					this.closeEmitter.emit(true);
					this.router.navigate(['user_login']).then();
				},
				error: e => {
					this.router.navigate(['user_login']).then();
				},
			}));
		}
	}
}
