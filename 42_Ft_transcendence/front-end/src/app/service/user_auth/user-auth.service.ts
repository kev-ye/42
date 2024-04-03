import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

import { Observable } from 'rxjs';

import { GlobalConsts } from 'src/app/common/global';

@Injectable({ providedIn: 'root' })
export class UserAuthService {
	USER_API: string = GlobalConsts.userApi;

	constructor(private httpClient: HttpClient) {}

	ftLogin() {
		window.location.href = `${this.USER_API}/user/auth/42/login`;
	}

	logout() {
		return this.httpClient.post<void>(`${this.USER_API}/user/auth/logout`, {}, {
			withCredentials: true
		});
	}

	isLogin(): Observable<boolean> {
    return this.httpClient.get<boolean>(`${this.USER_API}/user/isLogin`, {
			withCredentials: true
		})
  }

	twoFaGenerate(): Observable<any> {
		return this.httpClient.post<any>(`${this.USER_API}/user/auth/2fa/generate`, {}, {
			withCredentials: true
		})
	}

	twoFaVerify(token: any): Observable<any> {
		return this.httpClient.post<any>(`${GlobalConsts.userApi}/user/auth/2fa/verify`, token, {
			withCredentials: true
		})
	}

	twoFaTurnOff():  Observable<any> {
		return this.httpClient.delete<any>(`${this.USER_API}/user/auth/2fa/turnoff`, {
			withCredentials: true
		})
	}

	connexionRefresh():  Observable<any> {
		return this.httpClient.get<any>(`${this.USER_API}/user/isLogin/refresh`, {
			withCredentials: true
		})
	}
}
