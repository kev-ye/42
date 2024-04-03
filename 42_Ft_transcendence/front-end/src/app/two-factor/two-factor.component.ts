import { Component, OnDestroy, OnInit } from '@angular/core';
import { FormGroup, FormControl, Validators } from '@angular/forms';
import { Router } from '@angular/router';

import { Subscription } from "rxjs";

import { GlobalConsts } from '../common/global';
import { UserApiService } from '../service/user_api/user-api.service';
import { UserAuthService } from "../service/user_auth/user-auth.service";

@Component({
  selector: 'app-two-factor',
  templateUrl: './two-factor.component.html',
  styleUrls: ['./two-factor.component.css']
})
export class TwoFactorComponent implements OnInit, OnDestroy {
	title: string =  GlobalConsts.siteTitle;

	twoFactorForm: FormGroup = new FormGroup({
		token: new FormControl('', [
			Validators.required,
			Validators.pattern('^[0-9]*$')
		])
	})

	private subscription: Subscription = new Subscription();

  constructor(
		private router: Router,
		private userApi: UserApiService,
		private userAuth: UserAuthService) { }

  ngOnInit(): void {
		this.subscription.add(this.userApi.getUser().subscribe({
			next: (v) => {
				if (!v.twoFactorSecret)
					this.router.navigate(['main']).then();
			},
			error: (e) => {
				this.router.navigate(['main']).then();
			},
		}));
  }

	ngOnDestroy() {
		this.subscription.unsubscribe();
	}

	verify(): void {
		this.subscription.add(this.userAuth.twoFaVerify(this.twoFactorForm.value).subscribe({
			next: (v) => {
				if (v.delta === 0)
					this.router.navigate(['main']).then(_ => {});
				else
					window.alert((v.delta === -1)? 'Your token has expired' : 'Your Token is invalid');
			},
		}));
	}

}
