import { Injectable } from '@nestjs/common';
import { HttpService } from '@nestjs/axios';
import { PassportStrategy } from '@nestjs/passport';

import { Strategy } from 'passport-oauth2';
import { lastValueFrom } from 'rxjs';

import { UserDto } from 'src/user/dto/user.dto';
import { AuthService } from './auth.service';

@Injectable()
export class FortyTwoStrategy extends PassportStrategy(Strategy, '42') {
  constructor(
    private readonly authService: AuthService,
    private readonly httpService: HttpService,
  ) {
    super({
      authorizationURL: 'https://api.intra.42.fr/oauth/authorize',
      tokenURL: 'https://api.intra.42.fr/oauth/token',
      clientID:
        'f752289aff770bfe8f6828186c8440a238452f8dca8d4a95bc1754c46fbe9b92',
      clientSecret:
        '6c5184fd57bab51c34e8295917367ef31ddcacce0bdf36a5f7b023b74267d2ca',
      callbackURL: 'http://localhost:3000/pongApi/user/auth/42/callback',
      scope: ['public'],
    });
  }

  async validate(
    accessToken: string,
    refreshToken: string,
    profile: any,
    cb: any,
  ): Promise<any> {
    const getUser = lastValueFrom(
      this.httpService.get('https://api.intra.42.fr/v2/me', {
        headers: { Authorization: 'Bearer ' + accessToken },
      }),
    );

    const { id, login, email, image_url } = (await getUser).data;

    let user: UserDto = {
      id: id.toString(),
      login: login,
      name: '',
      avatar: '',
      fortyTwoAvatar: image_url,
      email: email,
      online: 1,
      twoFactorSecret: '',
      twoFactorQR: '',
    };

    if (login) user = await this.authService.ftValidUser(user);
    return cb(null, user);
  }
}
