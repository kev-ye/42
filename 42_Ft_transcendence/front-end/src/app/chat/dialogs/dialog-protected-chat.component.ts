import { HttpClient } from "@angular/common/http";
import { Component, ElementRef, Inject, OnInit, ViewChild } from "@angular/core";
import { MAT_DIALOG_DATA, MatDialogRef } from "@angular/material/dialog";
import { GlobalConsts } from "src/app/common/global";

@Component({
    selector: "dialog-protected-chat",
    templateUrl: "./html/dialog-protected-chat.html"
  })
  export class DialogProtectedChat implements OnInit{
    constructor(@Inject(MAT_DIALOG_DATA) public data: any, private http: HttpClient, private dialog: MatDialogRef<DialogProtectedChat>) {}
  
    chat_id: string = "";
    @ViewChild('error') error: ElementRef<HTMLDivElement>;
  
    ngOnInit(): void {
      this.chat_id = this.data.id;
        
    }
  
    submitPassword(password: string) {
      this.http.post(`${GlobalConsts.userApi}/channels/password/` + this.chat_id, {password: password}, {withCredentials: true}).subscribe({
        next: data => {
          if (data)
            this.dialog.close({success: true, password: password});
          else
          {
            this.error.nativeElement.textContent = "Password is wrong";
          }
        }
      })
    }
  }