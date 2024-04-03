import { Module } from '@nestjs/common';
import { AuthService } from './auth.service';
import { UserModule } from 'src/user/user.module';
import { PassportModule } from '@nestjs/passport';
import { FortyTwoStrategy } from './fortyTwo.strategy';
import { HttpModule } from '@nestjs/axios';
import { UserGuard } from './user.guard';

@Module({
  imports: [UserModule, PassportModule, HttpModule],
  providers: [AuthService, FortyTwoStrategy, UserGuard],
})
export class AuthModule {}
