import { Component, ViewChild } from '@angular/core';
import { WebSocketSubject, webSocket } from 'rxjs/webSocket';
import { Packet } from './packet';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'angular-client';

  socket$: WebSocketSubject<Packet>;

  @ViewChild("type")
  typeInput!: { nativeElement: { value: any; }; };
  @ViewChild("data")
  dataInput!: { nativeElement: { value: any; }; };

  constructor() {
    this.socket$ = webSocket<Packet>("ws://localhost:1337");

    this.socket$.subscribe(
      (message) => console.log(message),
      (err) => console.error(err),
      () => console.warn("Completed!")
    );
  }

  send() {
    let type = Number(this.typeInput.nativeElement.value);
    let payload = this.dataInput.nativeElement.value;

    let packet = new Packet(type, payload);
    this.socket$.next(packet);
  }
}
