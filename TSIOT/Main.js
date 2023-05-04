class Main {
    constructor() {
        this.api = new API();
        this.view = new ViewMainPage();
    }
    handleGETResponse(status, response) {
        this.devices = JSON.parse(response);
        this.view.showDevices(this.devices, this);
    }
    main() {
        this.api.requestGET("device", this);
        document.getElementById("boton").addEventListener("click", this);
    }
    handleEvent(evt) {
        let target = evt.target;
        let type = evt.type;
        if (target.id == "boton") {
            this.api.requestGET("device", this);
            console.log("handling boton");
        }
    }
}
window.onload = function () {
    let main = new Main();
    main.main();
};
