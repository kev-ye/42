import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { PrivateInviteEntity } from './entity/private-invite.entity';
import { PrivateInviteService } from './private-invite.service';

@Module({
  imports: [TypeOrmModule.forFeature([PrivateInviteEntity])],
  controllers: [],
  providers: [PrivateInviteService],
  exports: [PrivateInviteService]
})
export class PrivateInviteModule {}
