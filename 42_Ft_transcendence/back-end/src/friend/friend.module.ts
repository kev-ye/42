import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { FriendController } from './friend.controller';
import { FriendEntity } from './entity/friend.entity';
import { FriendService } from './friend.service';
import { UserModule } from 'src/user/user.module';
import { PlayersModule } from 'src/players/players.module';

@Module({
  imports: [ TypeOrmModule.forFeature([FriendEntity]), UserModule, PlayersModule],
  controllers: [FriendController],
  providers: [
    {
      provide: 'FRIEND_SERVICE',
      useClass: FriendService
    }
  ],
  exports: [
    {
      provide: 'FRIEND_SERVICE',
      useClass: FriendService
    }
  ]
  
})
export class FriendModule {}
