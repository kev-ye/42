import { Component, OnDestroy, OnInit } from '@angular/core';
import { FormGroup, FormControl, Validators } from '@angular/forms';
import { Router } from '@angular/router';

import { UserApiService } from '../service/user_api/user-api.service';
import { GlobalConsts } from '../common/global';
import { Subscription } from "rxjs";
import { DataSharedService } from "../service/data/data-shared.service";
import { UserAuthService } from "../service/user_auth/user-auth.service";

@Component({
  selector: 'app-user-subscription',
  templateUrl: './user-subscription.component.html',
  styleUrls: ['./user-subscription.component.css']
})
export class UserSubscriptionComponent implements OnInit, OnDestroy {
	title: string = GlobalConsts.siteTitle;
	isLogin: boolean = false;

	subscriptionForm: FormGroup = new FormGroup({
    name: new FormControl('', [
      Validators.required,
      Validators.minLength(6),
      Validators.pattern('^[a-zA-Z]*$')
    ])
  });

	private subscription: Subscription = new Subscription();

	constructor(
		private router: Router,
		private userAuth: UserAuthService,
		private userApi: UserApiService,
		private data: DataSharedService) { }

  ngOnInit(): void {}

	ngOnDestroy() {
		this.subscription.unsubscribe();
	}

	createUser() {
		const confirm$: boolean = confirm(`Create account with name: ${this.subscriptionForm.value.name} ?`)
		if (confirm$)
			this.subscription.add(this.userApi.createUser(this.subscriptionForm.value.name).subscribe({
				next: (v) => {
					if (v && v.name === this.subscriptionForm.value.name) {
						this.data.changeIsLoginData(true);
						this.router.navigate(['main']).then();
					}
					else
						alert('something wrong, try again!');
				},
				error: (e) => {
					this.router.navigate(['user_login']).then();
				},
			}));
  }

	cancel() {
		const confirm$: boolean = confirm('Are you sure?');
		if (confirm$) {
			this.subscription.add(this.userAuth.logout().subscribe({
				next: _ => {
					this.data.changeIsLoginData(false);
					this.router.navigate(['user_login']).then();
				},
				error: e => {
					this.router.navigate(['user_login']).then();
				},
			}));
		}
	}

	nameVerify() {
		this.subscription.add(this.userApi.nameVerify(this.subscriptionForm.value.name).subscribe({
			next: (v) => {
				if (v)
					alert('User name valid');
				else
					alert('User name no valid');
			},
			complete: () => {}
		}));
	}
}
