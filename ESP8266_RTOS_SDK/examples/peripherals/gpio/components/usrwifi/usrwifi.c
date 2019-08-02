#include "../../main/user_include.h"

/* Simple WiFi Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/


/* The examples use simple WiFi configuration that you can set via
   'make menuconfig'.

   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
#define EXAMPLE_ESP_WIFI_MODE_AP    CONFIG_ESP_WIFI_MODE_AP //TRUE:AP FALSE:STA
#define EXAMPLE_ESP_WIFI_SSID "Hello Vincent WIFI"//CONFIG_ESP_WIFI_SSID
#define EXAMPLE_ESP_WIFI_PASS       "1234567890"//CONFIG_ESP_WIFI_PASSWORD   //密码需要8位以上
#define EXAMPLE_MAX_STA_CONN        4//CONFIG_MAX_STA_CONN

#define CONFIG_ESP_WIFI_MODE_AP 1

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t wifi_event_group;

/* The event group allows multiple bits for each event,
   but we only care about one event - are we connected
   to the AP with an IP? 
*/ 
const int WIFI_CONNECTED_BIT = BIT0;

extern const char *TAG;

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    /* For accessing reason codes in case of disconnection */
    system_event_info_t *info = &event->event_info;

    switch (event->event_id)
    {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        ESP_LOGI(TAG, "got ip:%s",
                 ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_AP_STACONNECTED:
        ESP_LOGI(TAG, "station:" MACSTR " join, AID=%d",
                 MAC2STR(event->event_info.sta_connected.mac),
                 event->event_info.sta_connected.aid);
                 printWiFiInfo();
        break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
        ESP_LOGI(TAG, "station:" MACSTR " leave, AID=%d",
                 MAC2STR(event->event_info.sta_disconnected.mac),
                 event->event_info.sta_disconnected.aid);
                  printWiFiInfo();
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        ESP_LOGE(TAG, "Disconnect reason : %d", info->disconnected.reason);
        if (info->disconnected.reason == WIFI_REASON_BASIC_RATE_NOT_SUPPORT)
        {
            /*Switch to 802.11 bgn mode */
            esp_wifi_set_protocol(ESP_IF_WIFI_STA, WIFI_PROTOCAL_11B | WIFI_PROTOCAL_11G | WIFI_PROTOCAL_11N);
        }
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, WIFI_CONNECTED_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;
}

void wifi_init_softap()
{
    wifi_event_group = xEventGroupCreate(); //用于接收系统事件

    tcpip_adapter_init(); //实际主要是lwip_init();

    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL)); //循环监控事件并打印

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT(); //里面设置了系统事件的回调函数&esp_event_send等等一些参数
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .ssid_len = strlen(EXAMPLE_ESP_WIFI_SSID),
            .password = EXAMPLE_ESP_WIFI_PASS,
            .max_connection = EXAMPLE_MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK},
    };
    //printf("*****************************SSID:   %s\n\r", wifi_config.ap.ssid);
    printWiFiInfo();


    if (strlen(EXAMPLE_ESP_WIFI_PASS) == 0)
    {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_softap finished.SSID:%s password:%s",
             EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
}

void wifi_init_sta()
{
    wifi_event_group = xEventGroupCreate();

    tcpip_adapter_init();
    
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .password = EXAMPLE_ESP_WIFI_PASS},
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_sta finished.");
    ESP_LOGI(TAG, "connect to ap SSID:%s password:%s",
    EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);

}

void usrwifiInit(void)
{
    //Initialize NVS
    printWiFiInfo();
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

#if EXAMPLE_ESP_WIFI_MODE_AP
    ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
    wifi_init_softap();
#else
    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    wifi_init_sta();
#endif /*EXAMPLE_ESP_WIFI_MODE_AP*/

}


void printWiFiInfo(void)
{


    wifi_config_t wifi_inf;
/**
  * @brief     Get configuration of specified interface
  *
  * @param     interface  interface
  * @param[out]  conf  station or soft-AP configuration
  *
  * @return
  *    - ESP_OK: succeed
  *    - ESP_ERR_WIFI_NOT_INIT: WiFi is not initialized by esp_wifi_init
  *    - ESP_ERR_INVALID_ARG: invalid argument
  *    - ESP_ERR_WIFI_IF: invalid interface
  */
    esp_err_t errorCode=esp_wifi_get_config(ESP_IF_WIFI_AP,&wifi_inf);
    switch(errorCode)
    {
        case ESP_OK:
//         /** @brief Soft-AP configuration settings for the ESP8266 */
// typedef struct {
//     uint8_t ssid[32];           /**< SSID of ESP8266 soft-AP */
//     uint8_t password[64];       /**< Password of ESP8266 soft-AP */
//     uint8_t ssid_len;           /**< Length of SSID. If softap_config.ssid_len==0, check the SSID until there is a termination character; otherwise, set the SSID length according to softap_config.ssid_len. */
//     uint8_t channel;            /**< Channel of ESP8266 soft-AP */
//     wifi_auth_mode_t authmode;  /**< Auth mode of ESP8266 soft-AP. Do not support AUTH_WEP in soft-AP mode */
//     uint8_t ssid_hidden;        /**< Broadcast SSID or not, default 0, broadcast the SSID */
//     uint8_t max_connection;     /**< Max number of stations allowed to connect in, default 4, max 4 */
//     uint16_t beacon_interval;   /**< Beacon interval, 100 ~ 60000 ms, default 100 ms */
// } wifi_ap_config_t;
                    printf("*********SSID:              %s\n\r", wifi_inf.ap.ssid);
                    printf("*********PASSWORD:          %s\n\r", wifi_inf.ap.password);
                    printf("*********SSID_L:            %d\n\r", wifi_inf.ap.ssid_len);
                    printf("*********channel:           %d\n\r", wifi_inf.ap.channel);
                    printf("*********authmode:          %d\n\r", wifi_inf.ap.authmode);
                    printf("*********ssid_hidden:       %d\n\r", wifi_inf.ap.ssid_hidden);
                    printf("*********max_connection:    %d\n\r", wifi_inf.ap.max_connection);
                    printf("*********beacon_interval:   %u\n\r", wifi_inf.ap.beacon_interval);                 
            break;
        case ESP_ERR_WIFI_NOT_INIT:
                    printf("*********ESP_ERR_WIFI_NOT_INIT****\n\r");
            break;
        case ESP_ERR_INVALID_ARG:
                    printf("*********ESP_ERR_INVALID_ARG*****\n\r");
            break;
        case ESP_ERR_WIFI_IF:
                    printf("*********ESP_ERR_WIFI_IF*********\n\r");

            break;

    }

}