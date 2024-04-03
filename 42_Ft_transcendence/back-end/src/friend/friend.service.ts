import { Inject, Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { PlayersService } from 'src/players/players.service';
import { UserService } from 'src/user/user.service';
import { Repository } from 'typeorm';
import { FriendEntity } from './entity/friend.entity';

@Injectable()
export class FriendService {
  constructor(
    @InjectRepository(FriendEntity) private repo: Repository<FriendEntity>,
    @Inject('USER_SERVICE') private userService: UserService,
    private playerService: PlayersService
  ) {
  }

  async addFriend(data: { first: string; second: string }) {
    const tmp = await this.repo.findOne({
      where: [
        { first: data.first, second: data.second },
        { first: data.second, second: data.first },
      ],
    });
    if (!tmp) {
      if (!(await this.userService.getUserById(data.first)) && !(await this.userService.getUserById(data.second)))
        return null;
      //const user = await this.userService.findUser({id: data.first});

      const relation = this.repo.create({
        first: data.first,
        second: data.second,
        status: 1,
      });
      return await this.repo.save(relation);
    }
    if (tmp.status != 1) {
      return null;
    }
    if (tmp.first == data.first) {
      //if emitter of the invite is trying to add again -> don't do anything
      return null;
    }
    return await this.repo.update(
      { first: tmp.first, second: tmp.second },
      { status: 2 },
    );
  }

  //return list of user IDs who are friends with 'id'
  async getFriends(id: string) {
    const tmp = await this.repo.find({
      where: [{ first: id }, { second: id }],
    });
    
    const result = [];
    tmp.forEach((value) => {
      if (value.status) {
        if (value.first == id) //friend is second
        {
          result.push({ friend: value.second, status: value.status, emitter: value.first });

        }
        else //friend is first
        {
          result.push({ friend: value.first, status: value.status, emitter: value.first });
        }
      }
    });

    const final: any[] = [];
    for (const userID of result) {
      const friend = await this.userService.getUserById(userID.friend);
      if (friend)
      {
        const players = await this.playerService.getPlayerByUserId(friend.id);
        final.push({
          status: userID.status,
          username: friend.name,
          id: friend.id,
          playing: players && players.find(val => val.game_id) ? true : false,
          online: friend.online,
          avatar: friend.avatar,
          emitter: userID.emitter
        });
      }
    }
    return final;
  }

  async deleteFriend(data: { first: number; second: number }) {
    const tmp = await this.repo.findOne({
      where: [
        { first: data.first, second: data.second },
        { first: data.second, second: data.first },
      ],
    });
    if (!tmp) {
      return null;
    }

    await this.repo.remove(tmp);
    return 1;
  }
}
