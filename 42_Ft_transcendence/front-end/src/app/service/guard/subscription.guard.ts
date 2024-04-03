import { Injectable } from '@angular/core';
import {ActivatedRouteSnapshot, CanActivate, Router, RouterStateSnapshot, UrlTree} from '@angular/router';
import {catchError, map, Observable, of} from 'rxjs';
import {UserApiService} from "../user_api/user-api.service";

@Injectable({
  providedIn: 'root'
})
export class SubscriptionGuard implements CanActivate {
  constructor(
    private router: Router,
    private userApi: UserApiService) { }

  canActivate(
    route: ActivatedRouteSnapshot,
    state: RouterStateSnapshot): Observable<boolean> {
			return this.userApi.getUser()
				.pipe(
					map(user => {
						if (!user.name) return true;
						else {
							this.router.navigate(['main']).then();
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
