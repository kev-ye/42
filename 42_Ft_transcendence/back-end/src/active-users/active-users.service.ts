import { Inject, Injectable, OnModuleInit } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { UserService } from 'src/user/user.service';
import { Repository } from 'typeorm';
import { activeUserEntity } from './entity/activeUsers.entity';

@Injectable()
export class ActiveUsersService implements OnModuleInit {
    constructor(@InjectRepository(activeUserEntity) private repo: Repository<activeUserEntity>,
    @Inject('USER_SERVICE') private userService: UserService) {}
    
    onModuleInit() {
        this.repo.clear();
    }

    async getUser(userID: string) {
        return await this.repo.find({user_id: userID});
    }

    async getUsersByChatId(chat_id: string) {
        let tmp: any[] = await this.repo.find({where: {chat_id: chat_id}});
        let result: any[] = [];
        for (let val of tmp)
        {
            const user = await this.userService.getUserById(val.user_id);
            
            if (user)
            result.push({name: user.name, id: user.id})
        }
        return result;
    }

    async getUserBySocketId(socketID: string) {
        return await this.repo.findOne({where: {id: socketID}})
    }

    async removeUserBySocketId(id: string) {
        return await this.repo.delete({id: id});
    }

    async removeUserByUserId(id: string) {
        return await this.repo.delete({user_id: id});
    }

    async updateUser(data: any) {
        
        return await this.repo.update({id: data.id}, data)
    }

    async addUser(data: any) {
         
        const tmp = this.repo.create(data);
        return await this.repo.save(tmp);
    }
}
