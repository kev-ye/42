import { Component, OnInit } from '@angular/core';

import { UserAuthService } from '../service/user_auth/user-auth.service';
import { GlobalConsts } from '../common/global';

@Component({
  selector: 'app-user-login',
  templateUrl: './user-login.component.html',
  styleUrls: ['./user-login.component.css']
})
export class UserLoginComponent implements OnInit {

  title: string = GlobalConsts.siteTitle;
  icon: string = "login";
  buttonMsg: string = "Login with 42";

  constructor(private readonly userAuth: UserAuthService) {}

  ngOnInit() {}

  ftLogin() {
    this.userAuth.ftLogin();
  }
}
