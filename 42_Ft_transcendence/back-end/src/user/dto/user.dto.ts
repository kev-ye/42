export interface UserDto {
  id: string;
  login: string;
  name: string;
  avatar: string;
  fortyTwoAvatar: string;
  email: string;
  online: number; // 0: logout | 1: login | 2: in Game
  twoFactorSecret: string;
  twoFactorQR: string;
  // friends: string[];
  // history: HistoryDto[]; // ?
  // xp: number;
  // level: number;
  // updated: Date;
}

export interface LimitedUserDto {
  id: string;
  login: string;
  name: string;
  avatar: string;
  fortyTwoAvatar: string;
  email: string;
  online: number; // 0: logout | 1: login | 2: in Game
  twoFactorSecret: string;
  twoFactorQR: string;
}

export interface HistoryDto {
	id: string;
	user_id: string;
	status: boolean; // win or lose
}
