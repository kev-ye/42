import { Injectable } from '@nestjs/common';
import { UserDto } from './dto/user.dto';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { UserEntity } from './entity/user.entity';

@Injectable()
export class UserService {
  constructor(
    @InjectRepository(UserEntity)
    private usersRepository: Repository<UserEntity>,
  ) {}

  async getUsers(): Promise<UserDto[]> {
    return await this._getCompleteUsers();
  }

  async getUserById(id: string | undefined): Promise<UserDto> {
    if (id == undefined)
      return null;
    return (await this._getCompleteUsers()).find((user) => user.id === id);
  }

  async getUserByName(name: string): Promise<UserDto> {
    return (await this._getCompleteUsers()).find((user) => user.name === name);
  }

  async createUser(tmpUser: UserDto, name: string): Promise<UserDto | null> {
    if (!(await this.nameFormatVerify(name))) return null;
    else {
      const toCreate: UserDto = tmpUser;

      toCreate.name = name;
      return this.usersRepository.save(toCreate);
    }
  }

  async updateUser(user: UserDto): Promise<UserDto> {
    return this.usersRepository.save(user);
  }

  async updateUserByAuth(user: UserDto): Promise<UserDto> {
    const upUser: UserDto = user;

    return await this.getUserById(user.id).then((user) => {
      if (!user) return this.usersRepository.save(upUser);
      else {
        if (user.twoFactorSecret) user.online = 0;
        else user.online = 1;
        return this.usersRepository.save(user);
      }
    });
  }

  async nameFormatVerify(name: string): Promise<boolean> {
    if (!UserService._checkUserNameFormat(name)) return false;
    const check = await this._checkDuplicateName(name);
    return check;
  }

  /*
   * private
   */

  private async _getCompleteUsers(): Promise<UserDto[]> {
    return await this.usersRepository.find();
  }

  private static _checkUserNameFormat(username: string): boolean {
    return /^[a-zA-Z]{6,16}$/.test(username);
  }

  private async _checkDuplicateName(username: string): Promise<boolean> {
    return !(await this._getCompleteUsers()).find(
      (user) => user.name === username,
    );
  }
}
