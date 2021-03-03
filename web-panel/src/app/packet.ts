export class Packet {
    constructor(type: Number, payload: String) {
        this.type = type;
        this.payload = payload;
    }

    type: Number
    payload: String
}