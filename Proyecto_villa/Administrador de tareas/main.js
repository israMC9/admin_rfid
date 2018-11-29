window.vm = new Vue({
    el: "#app",
    data: {
        name: '',
        ram: '',
        hdd: '',
        prioridad: 1,
        list: "",
        timetotal: undefined,
        timecoming: undefined,

        procesosIniciados: [], 
        procesosTerminados: [], 
        // define los procesos actuales
        procesos: []
    },
    methods: {
        quitar (proceso) {
            if (this.procesosIniciados.length === 1) {
                    setTimeout(() => {
                        this.procesosTerminados.unshift(this.procesosIniciados[0])
                    }, this.procesosIniciados[0].timetotal * 1000);
                }
            setTimeout(() => {
                console.log(proceso.name, '--------------------')
                this.procesosIniciados = this.procesosIniciados.filter((elemento) => {
                    console.log(elemento.name, proceso.name, elemento != proceso)
                    if (elemento != proceso) {
                        console.log("se esta haciendo el un", proceso.name)
                        this.procesosTerminados.unshift(proceso)
                    }
                    
                    return elemento != proceso
                })


            }, proceso.timetotal * 1000)
        },
        insert () {
            const newprocess = {
                name: this.name,
                ram: this.ram,
                hdd: this.hdd,
                prioridad: this.prioridad,
                list: this.list,
                timetotal: this.timetotal,
                timecoming:this.timecoming,
                tll: new Date()
            }

            this.procesos.push(newprocess)  
            this.name = ""
            this.ram = ""
            this.hdd = ""
            this.prioridad-1
            this.list= ""
            this.timetotal= 0
            this.timecoming= 0

        },
        execute () {
            this.procesos.forEach(element => {
                setTimeout(() => {
                    this.procesosIniciados.unshift(element)
                    this.quitar(element)
                }, element.timecoming * 1000);
            })
        }
    }
})