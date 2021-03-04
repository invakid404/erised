import { Component, ViewChild } from '@angular/core';
import { WebSocketSubject, webSocket } from 'rxjs/webSocket';
import { Packet, PacketType } from './packet';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'angular-client';

  socket$: WebSocketSubject<Packet>;

  handlers: Array<(packet: Packet) => void>;

  systemInfo: any;
  widgets: Map<String, any>;

  @ViewChild("widgetContainer")
  widgetContainer!: { nativeElement: Element; getBoundingClientRect: () => { (): any; new(): any; left: number; top: number; }; };
  
  @ViewChild("data")
  dataInput!: { nativeElement: { value: any; }; };

  constructor() {
    console.log(this.map(400, 0, 400, 0, 1920))

    this.widgets = new Map<String, any>();

    this.handlers = new Array<(packet: Packet) => void>(PacketType.COUNT);

    this.handlers[PacketType.SYSTEM_INFO] = (packet: Packet) => {
      this.systemInfo = {};
      Object.assign(this.systemInfo, packet.payload);
    }

    this.handlers[PacketType.UPDATE] = (packet: Packet) => {
      let payload = packet.payload;
      console.log(payload);
      payload.forEach((widget: any) => {
        let widgetName = widget["name"];

        let widgetData = this.widgets.get(widgetName);
        if (!widgetData) {
          widgetData = {};
        }

        let [containerWidth, containerHeight] = this.getContainerSize();

        widget.pos.x = this.map(widget.pos.x, 0, this.systemInfo.resolution.x, 0, containerWidth);
        widget.pos.y = this.map(widget.pos.y, 0, this.systemInfo.resolution.y, 0, containerHeight);

        Object.assign(widgetData, widget);

        this.widgets.set(widgetName, widgetData);
      });
    }

    this.socket$ = webSocket<Packet>("ws://localhost:1337");

    this.socket$.subscribe(
      (packet) => this.handle(packet),
      (err) => console.error(err),
      () => console.warn("Completed!")
    );
  }

  widgetMoved(e: any, name: string) {
    let widgetData = this.widgets.get(name);

    let boxElement = document.getElementById(name)!;

    const left = e.pointerPosition.x - boxElement.getBoundingClientRect().left;
    const top = e.pointerPosition.y - boxElement.getBoundingClientRect().top;

    widgetData.pos.x = e.pointerPosition.x - left - this.widgetContainer.nativeElement.getBoundingClientRect().left;
    widgetData.pos.y = e.pointerPosition.y - top - this.widgetContainer.nativeElement.getBoundingClientRect().top;

    let [containerWidth, containerHeight] = this.getContainerSize();

    console.log(widgetData.pos);

    let updatePacket = new Packet(PacketType.UPDATE, [{
      name: name,
      pos: {
        x: this.map(widgetData.pos.x, 0, containerWidth, 0, this.systemInfo.resolution.x),
        y: this.map(widgetData.pos.y, 0, containerHeight, 0, this.systemInfo.resolution.y)
      }}]
    );

    this.widgets.set(name, widgetData);

    this.socket$.next(updatePacket);
  }

  handle(packet: Packet) {
    this.handlers[packet.type](packet);
  }

  getContainerSize() {
    let style = getComputedStyle(this.widgetContainer.nativeElement);

    return [Number(style.width.slice(0, -2)), Number(style.height.slice(0, -2))];
  }

  map(value: number, x1: number, y1: number, x2: number, y2: number) {
    return Math.round((value - x1) * (y2 - x2) / (y1 - x1) + x2);
  }
}
