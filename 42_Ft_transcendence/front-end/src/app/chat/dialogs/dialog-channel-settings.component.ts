import { HttpClient } from "@angular/common/http";
import { Component, Inject, ViewChild, ElementRef } from "@angular/core";
import { MatDialog, MatDialogRef, MAT_DIALOG_DATA } from "@angular/material/dialog";
import { GlobalConsts } from "src/app/common/global";
import { DialogBans } from "./dialog-bans.component";
import { DialogModerators } from "./dialog-moderators.component";

@Component({
    templateUrl: './html/dialog-channel-settings.html'
  })
  export class DialogChannelSettings {
    constructor(private http: HttpClient, private dialog: MatDialog, private dialogRef: MatDialogRef<DialogChannelSettings>, @Inject(MAT_DIALOG_DATA) public data: any) {
      this.chatName = data.name;
          
    }
  
    @ViewChild('printError') error: ElementRef<HTMLDivElement>;
  
    public chatName: string = "";
    private access: number = 0;
  
    passwordInput: boolean = false;
    
    hidePassword() {
      this.passwordInput = false;
    }
  
    showPassword() {
      this.passwordInput = true;
    }
  
    setAccess(val: any) {
      this.access = val;
      
    }

    openModerators() {
      this.dialog.open(DialogModerators,
        {
          data: {
            chat: {id: this.data.id, creator_id: this.data.creator_id}
          }
        });
    }

    openBans() {
      this.dialog.open(DialogBans,
        {
          data: {
            chat: {id: this.data.id, creator_id: this.data.creator_id}
          }
        });
    }
  
    changeChat(passwordOne: string, passwordTwo: string) {
      if (this.access == 1)
      {
        if (!passwordOne)
        {
          this.error.nativeElement.textContent = "Please enter password for protected channel";
          return ;
        }
        
        if (passwordOne != passwordTwo)
        {
          this.error.nativeElement.textContent = "Please enter same password"
          return ;
        }
        this.http.put(`${GlobalConsts.userApi}/channels`, {id: this.data.id, access: this.access, password: passwordOne}, {withCredentials: true}).subscribe({next:
                  data => {
                      this.dialogRef.close(true);
              },
            error: data => {
              this.error.nativeElement.textContent = "Could not create channel";
            }});
        return ;
      }
      this.http.put(`${GlobalConsts.userApi}/channels`, {id: this.data.id, access: this.access}, {withCredentials: true}).subscribe({next: 
              data => {
                  this.dialogRef.close(true);
                  
              },
              error: data => {
                this.error.nativeElement.textContent = "Could not update channel"
              }});
    }
  }