import { Inject, Injectable, Logger } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { MessageBody } from '@nestjs/websockets';
import { BanService } from 'src/ban/ban.service';
import { BlockService } from 'src/block/block.service';
import { ChatHistoryService } from 'src/chat-history/chat-history.service';
import { ModeratorService } from 'src/moderator/moderator.service';
import { MuteService } from 'src/mute/mute.service';
import { PrivateInviteService } from 'src/private-invite/private-invite.service';
import { UserService } from 'src/user/user.service';
import { Repository } from 'typeorm';
import { ChannelEntity } from './entity/channels.entity';
import * as argon from 'argon2'

@Injectable()
export class ChannelsService {
  constructor(
    @InjectRepository(ChannelEntity) private repo: Repository<ChannelEntity>,
    private modService: ModeratorService,
    private privateInvService: PrivateInviteService,
    @Inject('BAN_SERVICE') private banService: BanService,
    @Inject('MUTE_SERVICE') private muteService: MuteService,
    @Inject('USER_SERVICE') private userService: UserService,
    @Inject('CHAT_HISTORY_SERVICE') private historyService: ChatHistoryService,
    @Inject('BLOCK_SERVICE') private blockService: BlockService,
  ) {}

  async checkOwner(userID: string, data: { chat_id: string }) {
    if (!data || !data.chat_id) return false;
    const chan = await this.getChannelById(data.chat_id);
    if (!chan || chan.creator_id != userID) return false;
    return true;
  }

  async checkModerator(userID: string, data: { chat_id: string }) {
    if (!data || !data.chat_id) return false;

    const chan = await this.modService.isModerator(data.chat_id, userID);
    if (!chan) return false;
    return true;
  }

  async getAll(userID: string) {
    const tmp = await this.repo.find();
    for (const data of tmp) {
      const tab = await this.modService.getModeratorsByChatID(data.id);
      if (tab.find((val) => val.user_id == userID)) data['moderator'] = true;
      else data['moderator'] = false;

      if (data.creator_id && userID == data.creator_id) data['creator'] = true;
      else data['creator'] = false;
    }
    return tmp;
  }

  async getChannelById(id: string) {
    return await this.repo.findOne({ id: id });
  }

  async getChannelByName(name: string) {
    return await this.repo.findOne({ name: name });
  }

  async checkPassword(password: string, chat_id: string) {
    const tmp = await this.repo.findOne({ id: chat_id });
    if (tmp && tmp.access == 1 && tmp.password) {
      //check hashed version of password
      try
      {        
        return await argon.verify(tmp.password, password);
      }
      catch
      {
        return false;
      }
    }
    return false;
  }

  async checkAccess(userID: string, chatID: string) {
    const channel = await this.getChannelById(chatID);
    if (!channel) return 1;
    if (await this.banService.isBanned(userID, chatID)) return 2;
    else if (await this.modService.isModerator(chatID, userID)) return 0;
    if (channel.access == 2) {
      if (!(await this.privateInvService.isInvited(userID, chatID))) return 1;
    }
    return 0;
  }

  async updateById(userID: string, data: any) {
    return await this.repo.update(
      { id: data.id },
      { ...data, creator_id: userID },
    );
  }
  
  async deleteCreator(chatID: string) {
    return await this.repo.update({id: chatID}, {creator_id: null});
  }

  async createChannel(userID: string, data: any) {
    let result;
        
    if (data.access == 1)
      result = this.repo.create({ ...data, creator_id: userID, password: await argon.hash(data.password)});
    else
      result = this.repo.create({ ...data, creator_id: userID});

    if (!result) return;
    const tmp = (await this.repo.save(result)) as any;
    await this.modService.createModerator(userID, {
      user_id: data.creator_id,
      chat_id: tmp.id,
    });
    return tmp;
  }

  async createModerator(
    userID: string,
    data: { user_id: string; chat_id: string },
  ) {
    if (!(await this.checkOwner(userID, data))) return;

    return await this.modService.createModerator(userID, data);
  }

  async deleteModerator(
    userID: string,
    data: { chat_id: string; user_id: string },
  ) {
    if (!(await this.checkOwner(userID, data))) {
      return null;
    }

    return await this.modService.deleteModerator(userID, data);
  }

  async deleteAllModerator(
    userID: string,
    data: { chat_id: string; user_id: string },
  ) {
    if (!(await this.checkOwner(userID, data))) return;

    return await this.modService.deleteAllModerator(data);
  }

  async createMute(
    userID: string,
    data: { chat_id: string; user_id: string; date: Date },
  ) {
    if (!(await this.checkModerator(userID, data))) return;
    else if (await this.checkOwner(data.user_id, data)) return;

    return await this.muteService.addMute(data);
  }

  async deleteMute(userID: string, data: any) {
    if (!(await this.checkModerator(userID, data))) return;
    return await this.muteService.deleteMute(data);
  }

  async getMute(chatID: string, userID: string) {
    return await this.muteService.getMute(chatID, userID);
  }

  async banUser(userID: string, data: { user_id: string; chat_id: string }) {
    if (!(await this.checkModerator(userID, data))) return;
    else if (await this.checkOwner(data.user_id, data)) return;

    return await this.banService.banUser(data);
  }

  async getBanByChat(chatID: string) {
    return await this.banService.getBanByChat(chatID);
  }

  async getBanByUser(userID: string) {
    return await this.banService.getBanByUser(userID);
  }

  async isBanned(userID: string, chatID: string) {
    return await this.banService.isBanned(userID, chatID);
  }

  async deleteBan(userID: string, data: any) {
    if (!data || !data.chat_id || !data.user_id) return;
    if (!this.checkModerator(userID, data)) return;
    return await this.banService.deleteBan(data.user_id, data.chat_id);
  }

  async inviteToChannel(userID: string, data: any) {
    if (!(await this.checkModerator(userID, data))) return;
    const chan = this.repo.findOne({ id: data.chat_id });
    if (!chan) return;
    return await this.privateInvService.createInvite(data);
  }

  async inviteToChannelByName(userID: string, username: string, data: any) {
    const user = await this.userService.getUserByName(username);

    if (!(await this.checkModerator(userID, data))) return 2;
    if (!user) return 1;
    const chan = this.repo.findOne({ id: data.chat_id });
    if (!chan) return 3;
    await this.privateInvService.createInvite({
      user_id: user.id,
      chat_id: data.chat_id,
      emitter: userID,
    });
    return 0;
  }

  async deleteChannel(userID: string, chatID: string) {
    await this.repo.delete({id: chatID});
    await this.modService.deleteAllModerator({ chat_id: chatID });
    await this.muteService.deleteAllByChatId(chatID);
    await this.privateInvService.deleteAllByChat(chatID);
    await this.historyService.deleteByChatID(chatID);
    return await this.banService.deleteAllByChatId(chatID);
  }

  async getHistory(id: string, password?: string) {
    const tmp = await this.getChannelById(id);
    if (!tmp)
      return false;
    if (tmp.access == 1)
    {
      if (password == undefined)
        return false;
      if (!this.checkPassword(password, tmp.id)) 
        return false;
    }
    const res = await this.historyService.showChat(id);

    let lastResult: any[] = [];

    for (const val of res)
    {
      const tmp = await this.userService.getUserById(val.user_id);
      if (tmp)
        lastResult.push({...val, username: tmp.name});
    }      
    return lastResult;
  }
}
