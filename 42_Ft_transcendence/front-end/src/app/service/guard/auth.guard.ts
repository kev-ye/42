import { Injectable } from '@angular/core';
import { ActivatedRouteSnapshot, CanActivate, RouterStateSnapshot } from '@angular/router';
import { Router } from '@angular/router';

import { Observable, map, catchError, of } from 'rxjs';

import { UserApiService } from '../user_api/user-api.service';

@Injectable({ providedIn: 'root' })
export class AuthGuard implements CanActivate {
  constructor(
    private router: Router,
    private userApi: UserApiService) { }

  canActivate(
    route: ActivatedRouteSnapshot,
    state: RouterStateSnapshot): Observable<boolean> {
			return this.userApi.getUser()
				.pipe(
					map(user => {
						if (user.online === 1 && user.name) return true;
						else if (user.online === 1 && !user.name) {
							this.router.navigate(['user_subscription']).then();
							return false;
						}
						else if (user.online === 0 && user.twoFactorSecret) {
							this.router.navigate(['two_factor']).then();
							return false;
						}
						else {
							this.router.navigate(['user_login']).then();
							return false;
						}
					}),
					catchError(_ => {
						this.router.navigate(['user_login']).then();
						return of(false);
					})
				)
  }
}
