import { Injectable, Injector } from '@angular/core';
import { ActivatedRouteSnapshot, CanActivate, RouterStateSnapshot, UrlTree } from '@angular/router';
import {lastValueFrom, Observable} from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class CombinedGuard implements CanActivate {
	constructor(private injector: Injector) {
	}

  async canActivate(
    route: ActivatedRouteSnapshot,
    state: RouterStateSnapshot): Promise<boolean>  {
		const guards = route.data['guards'] || [];

		for (const guard of guards) {
			const instance: CanActivate = this.injector.get<CanActivate>(guard);
			let result = instance.canActivate(route, state);

			if (result instanceof Observable)
				result = await lastValueFrom(result);
			if (result === false)
				return false;
		}
		return true;
  }
}
