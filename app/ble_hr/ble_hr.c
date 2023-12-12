#include "ble_hr.h"

#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/services/hrs.h>



volatile bool ble_ready=false;
static const struct bt_data ad[] = {

    BT_DATA_BYTES(BT_DATA_FLAGS,(BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA_BYTES(BT_DATA_UUID16_ALL,BT_UUID_16_ENCODE(BT_UUID_HRS_VAL))


};


static void bt_ready(int err);

static int init_ble(void);


void ble_adv(void){

    init_ble();
    while(!ble_ready){

        printk("BLE stack not ready");
        k_msleep(100);

    }
    printk("BLE stack ready");
    int err;
    err = bt_le_adv_start(BT_LE_ADV_CONN_NAME,ad,ARRAY_SIZE(ad),NULL,0);
    if(err){
        printk("advertising failed %d",err);

    }

}
void hrs_notify(void)
{
    

	static uint8_t heartrate = 90U;

	/* Heartrate measurements simulation */
	heartrate++;
	if (heartrate == 160U) {
		heartrate = 90U;
	}

	bt_hrs_notify(heartrate);
}

static void bt_ready(int err){
    
    if(err){
        printk("bt enable return : %d",err);


    }
    printk("bt_ready!");
    ble_ready=true;
}
static int init_ble(void){

    printk("init ble");
    int err;
    err = bt_enable(bt_ready);
    if(err){

        printk("bt_enable failed (err %d)",err);
        return err;
    }

    return 0;
}