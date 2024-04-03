import { HttpClient } from "@angular/common/http";
import { Component, ElementRef, Inject, OnInit, ViewChild } from "@angular/core";
import { MAT_DIALOG_DATA, MatDialogRef } from "@angular/material/dialog";
import { GlobalConsts } from "src/app/common/global";

@Component({
    templateUrl: './html/dialog-change-username.html'
  })
  export class DialogChangeUsername implements OnInit {
  
    constructor(private http: HttpClient, @Inject(MAT_DIALOG_DATA) private data: any, private dialogRef: MatDialogRef<DialogChangeUsername>) {}
  
    change: boolean = false;
    userID : string = "";
  
    ngOnInit(): void {
        this.userID = this.data.id;
    }
  
    @ViewChild('statusText') private statusText: ElementRef<HTMLDivElement>;
  
    changeUsername(event: any, newUsername: string) {
      event.preventDefault();
      this.http.put(`${GlobalConsts.userApi}/user/update`, {id: this.userID, name: newUsername}, {withCredentials: true}).subscribe({
        next: data => {
          this.dialogRef.close(true);
        },
        error : data => {
          alert(data.error);
        }
      })
    }
  
    inputEvent(username: string) {
  
      if (username)
      {
        //look for username in database and see if available
        this.http.get(`${GlobalConsts.userApi}/user/name/` + username, {withCredentials: true}).subscribe({
          next: (data: any) => {
            if (!data)
            {
              this.statusText.nativeElement.textContent = username + " is available";
              this.change = true;
            }
            else
            {
              this.change = false;
              this.statusText.nativeElement.textContent = username + " is not available";
            }
          },
          error: data => {
            this.statusText.nativeElement.textContent = "Could not check for username";
            this.change = false;
          }
        });
      } else {
        this.change = false;
        this.statusText.nativeElement.textContent = "";
      }
  
    }
  }