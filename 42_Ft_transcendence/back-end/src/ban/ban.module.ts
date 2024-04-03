import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { UserModule } from 'src/user/user.module';
import { BanService } from './ban.service';
import { BanEntity } from './entity/ban.entity';

@Module({
  imports: [TypeOrmModule.forFeature([BanEntity]), UserModule],
  providers: [
    {
      provide: 'BAN_SERVICE',
      useClass: BanService,
    },
  ],
  exports: [
    {
      provide: 'BAN_SERVICE',
      useClass: BanService,
    },
  ],
  controllers: [],
})
export class BanModule {}
