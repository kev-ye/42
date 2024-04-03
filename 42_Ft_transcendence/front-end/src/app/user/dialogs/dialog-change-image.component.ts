import { HttpClient } from "@angular/common/http";
import { Component, ElementRef, Inject, ViewChild } from "@angular/core";
import { MatDialogRef, MAT_DIALOG_DATA } from "@angular/material/dialog";
import { GlobalConsts } from "src/app/common/global";

@Component({
    templateUrl: "./html/dialog-change-image.html"
  })
  export class DialogChangeImage {
    constructor(@Inject(MAT_DIALOG_DATA) private data: any, private http: HttpClient,
    private dialogRef: MatDialogRef<DialogChangeImage>) {
      this.link = `${GlobalConsts.userApi}/image/user/` + data.user_id + `?random=${Math.random()}`;
    }
  
    link: string = "";
    newImage: any;
  
    @ViewChild('file') file: ElementRef<HTMLInputElement>;
  
    changeImage(e: any) {
      if (!e.target.files || !e.target.files.item(0))
        return ;
      const reader = new FileReader();
      reader.readAsDataURL(e.target.files.item(0));
      if (reader)
      {
        reader.onload = (data: any) => {
          if (reader.result)
            this.link = reader.result.toString();
        };
      }
  
    }
  
  
    submitImage() {
  
      if (!this.file.nativeElement.files)
        return ;
  
      if (!this.file.nativeElement.files?.length)
      {
        return ;
      }
  
      const image = this.file.nativeElement.files.item(0);
      if (!image)
        return ;
  
        let ext: string = "";
        let index: number = 0;
  
        if ((index = ((image.name as string).lastIndexOf('.'))) > 0)
        {
          ext = (image.name as string).substring(index).toUpperCase();
  
          // if (ext != ".PNG" && ext != ".JPG")
          // {
          //   alert('Image extension is not authorized (.png or .jpg only)');
          //   return;
          // }
          let fd = new FormData();
          fd.append('image', image);
          this.http.post<FormData>(`${GlobalConsts.userApi}/image/upload/` + this.data.user_id, fd, {headers: {extension: ext}, withCredentials: true}).subscribe((res) => {
  
          });
        }
        this.dialogRef.close(this.link);
    }
  
    async deleteImage() {
      this.http.delete(`${GlobalConsts.userApi}/image/${this.data.user_id}`).subscribe( () => {
        this.dialogRef.close(`${GlobalConsts.userApi}/image/`);
      })
  
    }
  }