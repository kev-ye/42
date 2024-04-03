import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { UserModule } from 'src/user/user.module';
import { ActiveUsersController } from './active-users.controller';
import { ActiveUsersService } from './active-users.service';
import { activeUserEntity } from './entity/activeUsers.entity';

@Module({
  imports: [TypeOrmModule.forFeature([activeUserEntity]), UserModule],
  controllers: [ActiveUsersController],
  providers: [
    {
      provide: 'ACTIVE_USERS_SERVICE',
      useClass: ActiveUsersService
    }
  ],
  exports: [
    {
      provide: 'ACTIVE_USERS_SERVICE',
      useClass: ActiveUsersService
    }
  ]
})
export class ActiveUsersModule {}
