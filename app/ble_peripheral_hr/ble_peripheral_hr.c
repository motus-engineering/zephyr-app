#include "ble_interface.h"
#include "ble_peripheral_hr.h"

#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>




volatile bool ble_ready=false;
static const struct bt_data ad[] = {

    BT_DATA_BYTES(BT_DATA_FLAGS,(BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA_BYTES(BT_DATA_UUID16_ALL,BT_UUID_16_ENCODE(BT_UUID_HRS_VAL))


};


static void bt_ready(int err);

static void init_ble(void);


int ble_adv(void){

    init_ble();
    int err;
    err = BT_LE_ADV_START(BT_LE_ADV_CONN_NAME,ad,ARRAY_SIZE(ad),NULL,0);
    if(err){
        printk("advertising failed %d",err);

    }
    return err;
}
int hrs_notify(void)
{
    
    int err;
	static uint8_t heartrate = 90U;

	/* Heartrate measurements simulation */
	heartrate++;
	if (heartrate == 160U) {
		heartrate = 90U;
	}

	err = BT_HRS_NOTIFY(heartrate);
    return err;
}

static void bt_ready(int err){
    
    if(err){
        printk("bt enable return : %d",err);


    }
    printk("bt_ready!");
    ble_ready=true;
}
static void init_ble(void){

    printk("init ble");
    int err;
    err = BT_ENABLE(bt_ready);
   
    
    if(err){

        printk("bt_enable failed (err %d)",err);
        k_msleep(100);

    }
    printk("BLE stack ready");
}