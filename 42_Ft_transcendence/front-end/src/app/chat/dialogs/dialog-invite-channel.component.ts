import { HttpClient } from "@angular/common/http";
import { Component, ElementRef, Inject, ViewChild } from "@angular/core";
import { MAT_DIALOG_DATA } from "@angular/material/dialog";
import { GlobalConsts } from "src/app/common/global";

  @Component({
    selector: "dialog-invite",
    templateUrl: "./html/dialog-invite.html"
  })
  export class DialogInvite {
    constructor(@Inject(MAT_DIALOG_DATA) private data: any, private http: HttpClient) {}

    @ViewChild('output') output: ElementRef<HTMLDivElement>

    inviteFriend(friend: string) {
      //invite friend to channel
      this.http.post(`${GlobalConsts.userApi}/channels/invite/name`, {
        chat_id: this.data.chat.id,
        name: friend
      }, {withCredentials: true}).subscribe({next: res=> {
        if (!res)
          this.output.nativeElement.textContent = "User was invited to channel"
        else
          this.output.nativeElement.textContent = "Could not invite user"  
      },
    error: () => {
      this.output.nativeElement.textContent = "Could not invite user"
    }});
    }
  }