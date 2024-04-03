import { Injectable } from '@angular/core';
import {BehaviorSubject} from "rxjs";

@Injectable({
  providedIn: 'root'
})
export class DataSharedService {
	public isLoginData = new BehaviorSubject<boolean>(false);

  constructor() {}

	changeIsLoginData(value: boolean) {
		this.isLoginData.next(value);
	}
}
