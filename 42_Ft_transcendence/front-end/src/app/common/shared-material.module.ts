import { NgModule } from '@angular/core';
import { MatButtonModule } from '@angular/material/button';
import { MatIconModule } from '@angular/material/icon';
import { MatSidenavModule } from '@angular/material/sidenav';
import { MatToolbarModule } from '@angular/material/toolbar';
import { MatStepperModule } from '@angular/material/stepper';
import { MatFormFieldModule } from '@angular/material/form-field';
import { MatInput, MatInputModule } from '@angular/material/input';
import { MatListModule } from '@angular/material/list'
import { MatBadgeModule } from '@angular/material/badge'
import { MatTabsModule } from '@angular/material/tabs'
import { MatDialogModule } from '@angular/material/dialog'
import { MatCheckboxModule } from '@angular/material/checkbox';

@NgModule({
	imports: [
		MatButtonModule,
		MatIconModule,
		MatSidenavModule,
		MatToolbarModule,
		MatStepperModule,
		MatFormFieldModule,
		MatInputModule,
		MatBadgeModule,
		MatTabsModule,
		MatDialogModule,
		MatInputModule,
		MatCheckboxModule
	],
	exports: [
		MatButtonModule,
		MatIconModule,
		MatSidenavModule,
		MatToolbarModule,
		MatStepperModule,
		MatFormFieldModule,
		MatInputModule,
		MatListModule,
		MatBadgeModule,
		MatTabsModule,
		MatDialogModule,
		MatInputModule,
		MatCheckboxModule
	]
})
export class SharedMaterialModule { }
