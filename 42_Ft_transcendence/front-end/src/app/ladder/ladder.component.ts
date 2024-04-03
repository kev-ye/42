import { Component, OnInit } from '@angular/core';
import { MatDialog } from '@angular/material/dialog';
import { DialogUser } from '../chat/dialogs/dialog-user.component';

@Component({
  selector: 'app-ladder',
  templateUrl: './ladder.component.html',
  styleUrls: ['./ladder.component.css']
})
export class LadderComponent implements OnInit {

  constructor(public dialog: MatDialog) { }

  ngOnInit(): void {
  }

  openUser(user: string) {
    this.dialog.open(DialogUser, {
      data: {
        username: user//data
      }
    })
  }

}
