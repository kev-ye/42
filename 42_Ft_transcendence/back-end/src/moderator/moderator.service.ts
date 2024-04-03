import { Inject, Injectable, Logger } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { ChannelsService } from 'src/channels/channels.service';
import { Repository } from 'typeorm';
import { ModeratorEntity } from './entity/moderator.entity';

@Injectable()
export class ModeratorService {
    constructor(@InjectRepository(ModeratorEntity) private repo: Repository<ModeratorEntity>) {}

    async createModerator(userID: string, data: {user_id: string, chat_id: string}) {
        if (await this.repo.findOne({user_id: data.user_id, chat_id: data.chat_id}))
            return ;
        const tmp = this.repo.create(data);
        return await this.repo.save(tmp);
    }

    async deleteModerator(userID: string, data: {user_id: string, chat_id: string}) {
        Logger.log("deleting moderator")
        return await this.repo.delete({chat_id: data.chat_id, user_id: data.user_id});
    }

    async deleteAllModerator(data: {chat_id: string}) {
        return await this.repo.delete({chat_id: data.chat_id});
    }

    async isModerator(chatID: string, userID: string) {
        return await this.repo.findOne({chat_id: chatID, user_id: userID});
    }

    async getModeratorsByChatID(chat_id: string) {
        return await this.repo.find({chat_id: chat_id});
    }
}
