import { Module } from '@nestjs/common';
import { UserModule } from 'src/user/user.module';
import { ImageController } from './image.controller';
import { ImageService } from './image.service';

@Module({
  controllers: [ImageController],
  imports: [UserModule],
  providers: [
    {
      provide: 'IMAGE_SERVICE',
      useClass: ImageService
    }
  ],
  exports: [
    {
      provide: 'IMAGE_SERVICE',
      useClass: ImageService
    }
  ]
})
export class ImageModule {}
