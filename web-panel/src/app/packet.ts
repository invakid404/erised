export class Packet {
    constructor(type: number, payload: any) {
        this.type = type;
        this.payload = payload;
    }

    type: number
    payload: any
}

export enum PacketType {
    SYSTEM_INFO = 1,
    UPDATE,
    COUNT
}